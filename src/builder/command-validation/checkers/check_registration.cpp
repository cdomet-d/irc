/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_registration.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:45:57 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/11 12:31:02 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.hpp"

bool check::register_::stageDone(CmdSpec &cmd, size_t idx) {
	(void)idx;
	if (cmd.getSender().cliInfo.getRegistration() <= cmd.getRegistrationStage()
		|| cmd.getSender().cliInfo.getRegistration() == 3)
		return (true);
	if (cmd.getSender().cliInfo.getRegistration() == 1)
		RPL::send_(cmd.getSdFd(), ERR_NEEDNICKORUSER(cmd.getSdNick()));
	if (cmd.getSender().cliInfo.getRegistration() == 2) {
		if (cmd.getSdNick() != "*"
			&& (cmd.getName() == "NICK" || cmd.getName() == "PASS"))
			RPL::send_(cmd.getSdFd(), ERR_NEEDUSER(cmd.getSdNick()));
		else if (!cmd.getSender().cliInfo.getUsername().empty()
				 && (cmd.getName() == "USER" || cmd.getName() == "PASS"))
			RPL::send_(cmd.getSdFd(), ERR_NEEDNICK(cmd.getSdNick()));
		else
			return (true);
	}
	return (false);
}

bool check::register_::pwMatch(CmdSpec &cmd, size_t idx) {
	if (cmd[password_][idx] != cmd.serv_.getPass()) {
		RPL::send_(cmd.getSdFd(), ERR_PASSWDMISMATCH(cmd.getSdNick()));
		return (false);
	}
	return (true);
}

bool check::register_::isRegistered(CmdSpec &cmd, size_t idx) {
	(void)idx;
	if (cmd.getSender().cliInfo.getRegistration() == 3) {
		RPL::send_(cmd.getSdFd(), ERR_ALREADYREGISTERED(cmd.getSdNick()));
		return (false);
	}
	return (true);
}
