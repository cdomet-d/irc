/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Checkers.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:15:18 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/18 18:05:45 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Checkers.hpp"
#include "Log.h"
#include "syntaxCheck.hpp"

bool pwMatch(CmdSpec &cmd) {
	(void)cmd;
	return (0);
}

bool isRegistered(CmdSpec &cmd) {
	(void)cmd;
	return (0);
}

bool validNick(CmdSpec &cmd) {
	std::string nick = cmd[nickname][0];
	if (nick.size() > 9) {
		nick = syntaxCheck::nick::trim(nick);
		cmd[nickname].rmParam(0);
		cmd[nickname].setOneParam(nick);

	}
	if (!syntaxCheck::nick::isValid(nick, cmd))
		return false;
	if (conflictCheck::nick::inUse(nick, cmd.server_.getUsedNick(), cmd.getSender().getFd()))
		return false;
	logger(INFO, cmd[nickname][0] + " is valid nickname\n");
	return true;
}

bool validUser(CmdSpec &cmd) {
	(void)cmd;
	return (0);
}

bool validChan(CmdSpec &cmd) {
	stringVec param = cmd[channel].getInnerParam();
	messageValidator::printCmdParam(param, "innerParam");
	return (0);
}

bool joinChanRequest(CmdSpec &cmd) {
	if (validChan(cmd)) {
		for (size_t i = 0; i < cmd[channel].getSize(); i++)
			if (cmd[channel][i][0] != '#') {
				ERR_NOSUCHCHANNEL(cmd.getSender().cliInfo.getNick(),
								  cmd[channel][i]);
			}
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
	(void)cmd;
	return (0);
}

bool hasChanPriv(CmdSpec &cmd) {
	(void)cmd;
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
