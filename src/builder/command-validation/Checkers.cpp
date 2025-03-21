/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Checkers.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:15:18 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/21 13:49:53 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Checkers.hpp"
#include "Reply.hpp"
#include "syntaxCheck.hpp"
#include "printers.hpp"

bool pwMatch(CmdSpec &cmd) {
	if (cmd[password_][0] != cmd.server_.getPass()) {
		reply::send(cmd.getSender().getFd(),
					ERR_PASSWDMISMATCH(cmd.getSender().cliInfo.getNick()));
		return (false);
	}
	return (true);
}

bool isRegistered(CmdSpec &cmd) {
	//TODO : if NICK, USER et PASS ont deja ete fait
	//		et que la commande est refaite pendant le registration stage
	//		mettre message custom
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
	reply::send(reply::INFO, cmd[nickname_][0] + " is valid nickname\n");
	return true;
}

bool validUser(CmdSpec &cmd) {
	(void)cmd;
	return (true);
}

bool validChan(CmdSpec &cmd) {
	stringVec param = cmd[channel_].getInnerParam();
	print::cmdParam(param, "innerParam");
	return (0);
}

bool joinChanRequest(CmdSpec &cmd) {
	channelMap::iterator itChan;

	for (size_t i = 0; i < cmd[channel_].getSize(); i++) {
		//TODO: call coralie's function to check syntax of channel
		itChan = cmd.server_.getAllChan().find(cmd[channel_][i]);
		if (itChan == cmd.server_.getAllChan().end())
			continue;
		Channel chan = *itChan->second;
		//TODO: faire un tableau de pointeur sur fonction. chaque fonction est un des if ci-dessous
		//faire un namespace
		//boucler sur le tableau et si une fonction renvoie false faire rmParam et continue;
		if (!onChan(cmd)) {
			if (chan.getCliInChan().size() < chan.getMaxCli()) {
				if (chan.getModes().find('i') == std::string::npos ||
					(chan.getModes().find('i') != std::string::npos
					 /*&& sender has an invite*/)) {
					if (chan.getModes().find('k') == std::string::npos ||
						(chan.getModes().find('k') != std::string::npos &&
						 i < cmd[key_].getSize() &&
						 chan.getPassword() == cmd[key_][i])) {
						//TODO: faire un define pour client chan limit
						if (cmd.getSender().getJoinedChans().size() < 50)
							continue;
						reply::send(cmd.getSender().getFd(),
									ERR_TOOMANYCHANNELS(chan.getName()));
					}
					reply::send(
						cmd.getSender().getFd(),
						ERR_BADCHANNELKEY(cmd.getSender().cliInfo.getNick(),
										  chan.getName()));
				}
				reply::send(cmd.getSender().getFd(),
							ERR_INVITEONLYCHAN(chan.getName()));
			}
			reply::send(cmd.getSender().getFd(),
						ERR_CHANNELISFULL(chan.getName()));
		}
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
	channelMap::iterator itChan;

	itChan = cmd.server_.getAllChan().find(cmd[channel_][0]);
	Channel chan = *itChan->second;

	if (cmd.getName() == "TOPIC" &&
		(!cmd[topic_].getInnerParam().empty() ||
		 (chan.getModes().find('t') == std::string::npos))) {
		return (true);
	}

	clientMap::iterator itCl;

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
