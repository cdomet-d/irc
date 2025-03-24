/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Checkers.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:15:18 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/24 18:30:51 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Checkers.hpp"
#include "n_checkJoin.hpp"
#include "n_syntaxCheck.hpp"
#include "printers.hpp"
#include "Reply.hpp"

bool RegStageDone(CmdSpec &cmd) {
	if (cmd.getSender().cliInfo.getRegistration() <=
			cmd.getRegistrationStage() ||
		cmd.getSender().cliInfo.getRegistration() == 3)
		return (true);
	//TODO : refacto so there is juste one if else ?
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
	// reply::send(cmd.getSender().getFd(),
	// 			cmd[nickname_][0] + " is valid nickname\n");
	return true;
}

bool validUser(CmdSpec &cmd) {
	(void)cmd;
	return (true);
}

bool validChan(CmdSpec &cmd) {
	stringVec param = cmd[channel_].getInnerParam();
	print::cmdParam(param, "innerParam");
	return (true);
}

bool validRequest(Channel chan, CmdSpec &cmd, size_t i) {
	if (onChan(cmd))
		return (false);
	if (checkJoin::reachedChanLimit(chan, cmd.getSender()))
		return (false);
	if (chan.getModes().find("i") != std::string::npos &&
		!checkJoin::hasInvite(chan, cmd.getSender()))
		return (false);
	else if (chan.getModes().find("k") != std::string::npos &&
			 !checkJoin::validKey(chan, cmd[key_], i, cmd.getSender()))
		return (false);
	if (checkJoin::reachedCliChanLimit(chan, cmd.getSender()))
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

bool validMode(CmdSpec &cmd) {
	(void)cmd;
	return (true);
}

bool validMess(CmdSpec &cmd) {
	(void)cmd;
	return (true);
}
