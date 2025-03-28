/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Checkers.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:15:18 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/28 14:43:36 by aljulien         ###   ########.fr       */
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
			reply::send_(cmd.getSender().getFd(),
							 "Please enter nickname\r\n");
		else
			reply::send_(cmd.getSender().getFd(),
							 "Please enter username\r\n");
	}
	if (cmd.getName() == "NICK")
		reply::send_(cmd.getSender().getFd(), "Please enter username\r\n");
	return (false);
}

bool pwMatch(CmdSpec &cmd) {
	if (cmd[password_][0] != cmd.server_.getPass()) {
		reply::send_(cmd.getSender().getFd(),
						 ERR_PASSWDMISMATCH(cmd.getSender().cliInfo.getNick()));
		return (false);
	}
	return (true);
}

bool isRegistered(CmdSpec &cmd) {
	if (cmd.getSender().cliInfo.getRegistration() == 3) {
		reply::send_(
			cmd.getSender().getFd(),
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
	return true;
}

bool validUser(CmdSpec &cmd) {
	(void)cmd;
	return (true);
}

bool validChan(CmdSpec &cmd) {
	stringVec param = cmd[channel_].getInnerParam();
	//print::cmdParam(param, "innerParam");
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

	for (size_t i = 0; i < cmd[channel_].size(); i++) {
		//TODO: call coralie's function to check syntax of channel
		itChan = cmd.server_.getAllChan().find(cmd[channel_][i]);
		if (itChan == cmd.server_.getAllChan().end())
			continue;
		if (!validRequest(*itChan->second, cmd, i))
			cmd[channel_].rmParam(i);
	}
	if (!cmd[channel_].size())
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
		reply::send_(cmd.getSender().getFd(),
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
		reply::send_(cmd.getSender().getFd(),
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

/* Returns SET, UNSER or SET_ERR */
static e_mdeset checkModeset(char c) {
	switch (c) {
	case '+':
		return SET;
	case '-':
		return UNSET;
	default:
		return SET_ERR;
	}
}

/* Returns one of the following: B, C, D, TYPE_ERR */
static e_mdetype checkModetype(char c) {
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

/* for the current flag, recover type of setchar [+ | -] and type of flagtype [i | k | l | o | t]
Sends the ERR_UNKNOWN PARAM if they don't exist, the return an error.
if returns an error if they don't exist */
static bool assessFlag(e_mdeset &set, e_mdetype &type, const std::string &flag,
					   const Client &cli) {
	try {
		set = checkModeset(flag.at(0));
		type = checkModetype(flag.at(1));
	} catch (std::exception &e) { return false; }
	if (!set || !type) {
		reply::send(cli.getFd(),
					ERR_UNKNOWNMODE(cli.cliInfo.getNick(),
									(!set ? flag.at(0) : flag.at(1))));
		return false;
	}
	return true;
}

bool validMode(CmdSpec &cmd) {
	e_mdetype type;
	e_mdeset set;
	stringVec flags, param;

	if (cmd[flag_].empty()) {
		return true;
	}

	size_t size;
	for (size_t i = 0; i < cmd[flag_].size();) {
		size = cmd[flag_].size();
		if (!assessFlag(set, type, cmd[flag_][i], cmd.getSender()))
			return false;
		// if we MUST have a param and we don't, erase the flag
		if (((type == B) || (type == C && set == SET)) &&
			i >= cmd[flagArg_].size())
			cmd[flag_].rmParam(i);
		// else if we don't need a parameter, and cmd[flagArg_] is empty, we add a blank space at str.begin()
		else if (cmd[flagArg_].empty() &&
				 ((type == C && set == UNSET) || type == D))
			cmd[flagArg_].addOne(i);
		// else if we don't need a parameter, and cmd[flagArg_] is not, we add a blank space at i
		else if ((type == C && set == UNSET) || type == D)
			cmd[flagArg_].addOne(i);
		// increment if no cmd[flag_] were removed
		if (size == cmd[flag_].size())
			i++;
	}
	if (cmd[flag_].empty())
		reply::send(
			cmd.getSender().getFd(),
			ERR_NEEDMOREPARAMS(cmd.getSender().cliInfo.getNick(), "Mode"));
	return true;
}