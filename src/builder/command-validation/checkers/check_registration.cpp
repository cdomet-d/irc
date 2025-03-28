/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_registration.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlotte <charlotte@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:45:57 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/28 15:41:06 by charlotte        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.hpp"

bool check::register_::stageDone(CmdSpec &cmd) {
	//TODO: can there be only on if else ?
	if (cmd.getSender().cliInfo.getRegistration() <=
			cmd.getRegistrationStage() ||
		cmd.getSender().cliInfo.getRegistration() == 3)
		return (true);
	if (cmd.getName() == "PASS") {
		if (cmd.getSender().cliInfo.getRegistration() == 1)
			reply::send_(cmd.getSender().getFd(), "Please enter nickname\r\n");
		else
			reply::send_(cmd.getSender().getFd(), "Please enter username\r\n");
	}
	if (cmd.getName() == "NICK")
		reply::send_(cmd.getSender().getFd(), "Please enter username\r\n");
	return (false);
}

bool check::register_::pwMatch(CmdSpec &cmd) {
	if (cmd[password_][0] != cmd.server_.getPass()) {
		reply::send_(cmd.getSender().getFd(),
					ERR_PASSWDMISMATCH(cmd.getSender().cliInfo.getNick()));
		return (false);
	}
	return (true);
}

bool check::register_::isRegistered(CmdSpec &cmd) {
	if (cmd.getSender().cliInfo.getRegistration() == 3) {
		reply::send_(cmd.getSender().getFd(),
					ERR_ALREADYREGISTRED(cmd.getSender().cliInfo.getNick()));
		return (false);
	}
	return (true);
}
