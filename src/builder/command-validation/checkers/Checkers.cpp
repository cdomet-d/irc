/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Checkers.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:15:18 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/26 13:50:40 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Checkers.hpp"
#include "JoinRequestCheck.hpp"
#include "Reply.hpp"
#include "printers.hpp"

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



bool validUser(CmdSpec &cmd) {
	(void)cmd;
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




bool validKick(CmdSpec &cmd) {
	(void)cmd;
	return (true);
}

bool validMess(CmdSpec &cmd) {
	(void)cmd;
	return (true);
}
