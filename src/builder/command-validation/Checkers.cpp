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
	if (cmd[password_][0] != cmd.server_.getPass()) {
		// sendReply(cmd.getSender().getFd(),
		// 		  ERR_PASSWDMISMATCH(cmd.getSender().cliInfo.getNick()));
		std::cout << ERR_PASSWDMISMATCH(cmd.getSender().cliInfo.getNick());
		return (false);
	}
	return (true);
}

bool isRegistered(CmdSpec &cmd) {
	//TODO : si PASS a deja ete fait mais que la registration n'est pas fini que faire ?
	if (cmd.getSender().cliInfo.getRegistration() == 3) {
		// sendReply(cmd.getSender().getFd(),
		// 		  ERR_ALREADYREGISTRED(cmd.getSender().cliInfo.getNick()));
		std::cout << ERR_ALREADYREGISTRED(cmd.getSender().cliInfo.getNick());
		return (false);
	}
	return (true);
}

bool validNick(CmdSpec &cmd) {
	(void)cmd;
	return (true);
}

bool validUser(CmdSpec &cmd) {
	(void)cmd;
	return (true);
}

bool validChan(CmdSpec &cmd) {
	(void)cmd;
	return (true);
}

bool joinChanRequest(CmdSpec &cmd) {
	for (size_t i = 0; i < cmd[channel_].getSize(); i++)
		if (cmd[channel_][i][0] != '#') {
			// sendReply(cmd.getSender().getFd(),
			// 		  ERR_NOSUCHCHANNEL(cmd.getSender().cliInfo.getNick(),
			// cmd[channel_][i]));
		}
	//supprimer chaque channel faux, (ainsi que toutes les keys ? peut etre pas necessaire)
	//pour qu'il reste que les channel valide a join pour l'exec
	//s'ils ont tous ete supprimes mettre valid a false
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
	channelMap::iterator itChan;
	clientMap::iterator itCl;

	itChan = cmd.server_.getAllChan().find(cmd[channel_][0]);
	Channel chan = *itChan->second;
	itCl = chan.getCliInChan().find(cmd.getSender().getFd());
	if (itCl == chan.getCliInChan().end()) {
		// sendReply(cmd.getSender().getFd(),
		// 		  ERR_NOTONCHANNEL(cmd.getSender().cliInfo.getNick(),
		//    chan.getName()));
		std::cout << ERR_NOTONCHANNEL(cmd.getSender().cliInfo.getNick(),
									  chan.getName());
		return (false);
	}
	return (true);
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
		// sendReply(cmd.getSender().getFd(),
		// 		  ERR_CHANOPRIVSNEEDED(cmd.getSender().cliInfo.getNick(),
		//    chan.getName()));
		std::cout << ERR_CHANOPRIVSNEEDED(cmd.getSender().cliInfo.getNick(),
										  chan.getName());
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
