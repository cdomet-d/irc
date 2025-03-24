/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Checkers.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:15:18 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/24 17:44:38 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Checkers.hpp"
#include "JoinRequestCheck.hpp"
#include "Reply.hpp"
#include "printers.hpp"
#include "syntaxCheck.hpp"

bool RegStageDone(CmdSpec &cmd) {
	if (cmd.getSender().cliInfo.getRegistration() <=
			cmd.getRegistrationStage() ||
		cmd.getSender().cliInfo.getRegistration() == 3)
		return (true);
	if (cmd.getName() == "PASS") {
		if (cmd.getSender().cliInfo.getRegistration() == 1)
			reply::send(cmd.getSender().getFd(), "Please enter nickname\r\n");
		else
			reply::send(cmd.getSender().getFd(), "Please enter username\r\n");
	}
	if (cmd.getName() == "NICK")
		reply::send(cmd.getSender().getFd(), "Please enter username\r\n");
	return (false);
}

bool pwMatch(CmdSpec &cmd) {
	if (cmd[password_][0] != cmd.server_.getPass()) {
		reply::send(cmd.getSender().getFd(),
					ERR_PASSWDMISMATCH(cmd.getSender().cliInfo.getNick()));
		return (false);
	}
	return (true);
}

bool isRegistered(CmdSpec &cmd) {
	if (cmd.getSender().cliInfo.getRegistration() == 3) {
		reply::send(cmd.getSender().getFd(),
					ERR_ALREADYREGISTRED(cmd.getSender().cliInfo.getNick()));
		return (false);
	}
	return (true);
}

bool validNick(CmdSpec &cmd) {
	std::string nick = cmd[nickname_][0];
	if (nick.size() > 9) {
		nick = syntaxCheck::nick::trim(nick);
		cmd[nickname_].rmParam(0);
		cmd[nickname_].setOneParam(nick);
	}
	if (!syntaxCheck::nick::isValid(nick, cmd))
		return false;
	if (conflictCheck::nick::inUse(nick, cmd.server_.getUsedNick(),
								   cmd.getSender().getFd()))
		return false;
	reply::send(cmd.getSender().getFd(),
				cmd[nickname_][0] + " is valid nickname\n");
	return true;
}

bool validUser(CmdSpec &cmd) {
	(void)cmd;
	return (true);
}

bool validChan(CmdSpec &cmd) {
	stringVec param = cmd[channel_].getInnerParam();
	return (true);
}

bool validRequest(Channel chan, CmdSpec &cmd, size_t i) {
	if (onChan(cmd))
		return (false);
	if (joinCheck::reachedChanLimit(chan, cmd.getSender()))
		return (false);
	if (chan.getModes().find("i") != std::string::npos &&
		!joinCheck::hasInvite(chan, cmd.getSender()))
		return (false);
	else if (chan.getModes().find("k") != std::string::npos &&
			 !joinCheck::validKey(chan, cmd[key_], i, cmd.getSender()))
		return (false);
	if (joinCheck::reachedCliChanLimit(chan, cmd.getSender()))
		return (false);
	return (true);
}

bool joinChanRequest(CmdSpec &cmd) {
	channelMap::const_iterator itChan;

	for (size_t i = 0; i < cmd[channel_].getSize(); i++) {
		//TODO: call coralie's function to check syntax of channel
		itChan = cmd.server_.getAllChan().find(cmd[channel_][i]);
		if (itChan == cmd.server_.getAllChan().end())
			continue;
		if (!validRequest(*itChan->second, cmd, i))
			cmd[channel_].rmParam(i);
	}
	if (!cmd[channel_].getSize())
		return (false);
	return (true);
}

bool validTarget(CmdSpec &cmd) {
	(void)cmd;
	return (true);
}

bool validInvite(CmdSpec &cmd) {
	(void)cmd;
	return (true);
}

bool onChan(CmdSpec &cmd) {
	const stringVec &joinedChans = cmd.getSender().getJoinedChans();
	for (size_t i = 0; i < joinedChans.size(); i++) {
		if (joinedChans[i] == cmd[channel_][0])
			return (true);
	}
	if (cmd.getName() != "JOIN")
		reply::send(cmd.getSender().getFd(),
					ERR_NOTONCHANNEL(cmd.getSender().cliInfo.getNick(),
									 cmd[channel_][0]));
	return (false);
}

bool hasChanPriv(CmdSpec &cmd) {
	channelMap::const_iterator itChan;

	itChan = cmd.server_.getAllChan().find(cmd[channel_][0]);
	Channel chan = *itChan->second;

	if (cmd.getName() == "TOPIC" &&
		(!cmd[topic_].getInnerParam().empty() ||
		 (chan.getModes().find('t') == std::string::npos))) {
		return (true);
	}

	clientMap::const_iterator itCl;

	itCl = chan.getOpCli().find(cmd.getSender().getFd());
	if (itCl == chan.getOpCli().end()) {
		reply::send(cmd.getSender().getFd(),
					ERR_CHANOPRIVSNEEDED(cmd.getSender().cliInfo.getNick(),
										 chan.getName()));
		return (false);
	}
	return (true);
}

bool validKick(CmdSpec &cmd) {
	(void)cmd;
	return (true);
}

bool validMess(CmdSpec &cmd) {
	(void)cmd;
	return (true);
}

static e_modeset checkModeset(char c) {
	switch (c) {
	case '+':
		return SET;
	case '-':
		return UNSET;
	default:
		return SET_ERR;
	}
}

static e_modetype checkModetype(char c) {
	switch (c) {
	case 'i':
		return D;
	case 'k':
		return C;
	case 'l':
		return C;
	case 'o':
		return B;
	case 't':
		return D;
	default:
		return TYPE_ERR;
	}
}

// TYPE B: always MUST have a param
// TYPE C: MUST have a param when set, MUST NOT have a param when unset
// TYPE D: MUST NOT have a param

bool validMode(CmdSpec &cmd) {
	e_modetype type;
	e_modeset set;
	stringVec flags, param;

	try {
		flags = cmd[flag_].getInnerParam();
		param = cmd[flagArg_].getInnerParam();
	} catch (std::exception &e) { return false; }
	
	if (flags.size() == 0) {
		std::cout << "No modestring provided" << std::endl;
		return false;
	}
	print::cmdParam(cmd[flag_].getInnerParam(), "flags:");
	print::cmdParam(cmd[flagArg_].getInnerParam(), "flags params:");

	// iterate on the flag list
	for (size_t i = 0; i < flags.size();) {
	std::cout << "-----------------" << std::endl;
	size_t size = flags.size();
		// for i, recover setchar and flagtype; exit if either doesn't exist
		try {
			set = checkModeset(flags.at(i).at(0));
			type = checkModetype(flags.at(i).at(1));
			if (!set || !type) {
				reply::send(cmd.getSender().getFd(),
							ERR_UNKNOWNMODE(cmd.getSender().cliInfo.getNick(),
											flags.at(i).at(1)));
				return false;
			}
		} catch (std::exception &e) { 
		std::cerr << "i: " << i << ":	" << e.what() << std::endl; }
		
		std::cout << "For i [" << i << "] | " << flags.at(i) << std::endl;
		print::modeEnumToString(set, type);

		// check that we can access the param at the flag index
		
		// if we MUST have a param and we don't, erase the flag
		if (((type == B) || (type == C && set == SET)) && i > param.size()) {
			std::cout << "Must have param, but not enough param" << std::endl;
			flags.erase(flags.begin() + i);
		} 
		// if we don't need a parameter, we add a blank space
		else if ((type == C && set == UNSET) || type == D)
			param.insert(param.begin() + i, "");

		// if we don't need a parameter but we do have one ? 
		if (size == flags.size())
			i++;
	}
	std::cout << "-----------------" << std::endl;
	cmd[flag_].setParamList(flags);
	cmd[flagArg_].setParamList(param);
	print::cmdParam(cmd[flag_].getInnerParam(), "after: flags:");
	print::cmdParam(cmd[flagArg_].getInnerParam(), "after: flags params:");
	return (true);
}