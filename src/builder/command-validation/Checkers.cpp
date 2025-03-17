/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Checkers.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:15:18 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/17 18:25:00 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Checkers.hpp"

bool pwMatch(CmdSpec &cmd) {
	// if (cmd[password][0] != cmd.server_.) //TODO: add un getPass in server.hpp
	return (0);
}

bool isRegistered(CmdSpec &cmd) {
	if (cmd.getSender().cliInfo.getRegistration() == 3) {
		sendReply(cmd.getSender().getFd(),
				  ERR_ALREADYREGISTRED(cmd.getSender().cliInfo.getNick()));
		return (1);
	}
	return (0);
}

bool validNick(CmdSpec &cmd) {
	(void)cmd;
	return (0);
}

bool validUser(CmdSpec &cmd) {
	(void)cmd;
	return (0);
}

bool validChan(CmdSpec &cmd) {
	(void)cmd;
	return (0);
}

bool joinChanRequest(CmdSpec &cmd) {
	for (size_t i = 0; i < cmd[channel].getSize(); i++)
		if (cmd[channel][i][0] != '#') {
			sendReply(cmd.getSender().getFd(),
					  ERR_NOSUCHCHANNEL(cmd.getSender().cliInfo.getNick(),
										cmd[channel][i]));
		}
	//supprimer chaque channel faux, (ainsi que toutes les keys ? peut etre pas necessaire)
	//pour qu'il reste que les channel valide a join pour l'exec
	//s'ils ont tous ete supprimes mettre valid a false
	return (0);
}

bool validTarget(CmdSpec &cmd) {
	(void)cmd;
	return (0);
}

bool validInvite(CmdSpec &cmd) {
	(void)cmd;
	return (0);
}

bool onChan(CmdSpec &cmd) {
	channelMap::iterator itChan;
	clientMap::iterator itCl;

	itChan = cmd.server_.getAllChan().find(cmd[channel][0]);
	Channel chan = *itChan->second;
	itCl = chan.getCliInChan().find(cmd.getSender().getFd());
	if (itCl == chan.getOpCli().end()) {
		sendReply(cmd.getSender().getFd(),
				  ERR_NOTONCHANNEL(cmd.getSender().cliInfo.getNick(),
								   chan.getName()));
		return (1);
	}
	return (0);
}

bool hasChanPriv(CmdSpec &cmd) {
	channelMap::iterator itChan;

	itChan = cmd.server_.getAllChan().find(cmd[channel][0]);
	Channel chan = *itChan->second;

	if (cmd.getName() == "TOPIC" &&
		(!cmd[topic_].getInnerParam().empty() ||
		 (chan.getModes().find('t') == std::string::npos))) {
		return (0);
	}

	clientMap::iterator itCl;

	itCl = chan.getOpCli().find(cmd.getSender().getFd());
	if (itCl == chan.getOpCli().end()) {
		sendReply(cmd.getSender().getFd(),
				  ERR_CHANOPRIVSNEEDED(cmd.getSender().cliInfo.getNick(),
									   chan.getName()));
		return (1);
	}
	return (0);
}

bool validKick(CmdSpec &cmd) {
	(void)cmd;
	return (0);
}

bool validMode(CmdSpec &cmd) {
	(void)cmd;
	return (0);
}

bool validMess(CmdSpec &cmd) {
	(void)cmd;
	return (0);
}
