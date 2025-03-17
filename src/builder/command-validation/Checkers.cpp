/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Checkers.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:15:18 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/17 17:10:18 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Checkers.hpp"

bool pwMatch(CmdSpec &cmd) {
	(void)cmd;
	return (0);
}

bool isRegistered(CmdSpec &cmd) {
	(void)cmd;
	return (0);
}

int validNick(CmdSpec &cmd) {
	stringVec param = cmd[nickname].getInnerParam();
	messageValidator::printCmdParam(param, "innerParam");
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
			ERR_NOSUCHCHANNEL(cmd.getSender().cliInfo.getNick(),
							  cmd[channel][i]);
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
