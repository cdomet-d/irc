/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_registration.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:45:57 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/09 16:22:11 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.hpp"

bool check::register_::stageDone(CmdSpec &cmd, size_t idx) {
	(void)idx;
	if (cmd.getSender().cliInfo.getRegistration() <= cmd.getRegistrationStage()
		|| cmd.getSender().cliInfo.getRegistration() == 3)
		return (true);
	if (cmd.getSender().cliInfo.getRegistration() == 1)
		reply::send_(cmd.getSdFd(), ERR_NEEDNICKORUSER(cmd.getSdNick()));
	if (cmd.getSender().cliInfo.getRegistration() == 2) {
		if (cmd.getSdNick() != "*"
			&& (cmd.getName() == "NICK" || cmd.getName() == "PASS"))
			reply::send_(cmd.getSdFd(), ERR_NEEDUSER(cmd.getSdNick()));
		else if (!cmd.getSender().cliInfo.getUsername().empty()
				 && (cmd.getName() == "USER" || cmd.getName() == "PASS"))
			reply::send_(cmd.getSdFd(), ERR_NEEDNICK(cmd.getSdNick()));
		else
			return (true);
	}
	return (false);
}

bool check::register_::pwMatch(CmdSpec &cmd, size_t idx) {
	if (cmd[password_][idx] != cmd.serv_.getPass()) {
		reply::send_(cmd.getSdFd(), ERR_PASSWDMISMATCH(cmd.getSdNick()));
		return (false);
	}
	return (true);
}

bool check::register_::isRegistered(CmdSpec &cmd, size_t idx) {
	(void)idx;
	if (cmd.getSender().cliInfo.getRegistration() == 3) {
		reply::send_(cmd.getSdFd(), ERR_ALREADYREGISTERED(cmd.getSdNick()));
		return (false);
	}
	return (true);
}
