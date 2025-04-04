/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_registration.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:45:57 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/03 15:59:37 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.hpp"

bool check::register_::stageDone(CmdSpec &cmd, int idx) {
	(void)idx;
	if (cmd.getSender().cliInfo.getRegistration() <=
			cmd.getRegistrationStage() ||
		cmd.getSender().cliInfo.getRegistration() == 3)
		return (true);
	if (cmd.getSender().cliInfo.getRegistration() == 1)
		reply::send_(cmd.getSender().getFd(),
					 ERR_NEEDNICKORUSER(cmd.getSender().cliInfo.getNick()));
	if (cmd.getSender().cliInfo.getRegistration() == 2) {
		if (cmd.getSender().cliInfo.getNick() != "*" &&
			(cmd.getName() == "NICK" || cmd.getName() == "PASS"))
			reply::send_(cmd.getSender().getFd(),
						 ERR_NEEDUSER(cmd.getSender().cliInfo.getNick()));
		else if (!cmd.getSender().cliInfo.getUsername().empty() &&
				 (cmd.getName() == "USER" || cmd.getName() == "PASS"))
			reply::send_(cmd.getSender().getFd(),
						 ERR_NEEDNICK(cmd.getSender().cliInfo.getNick()));
		else
			return (true);
	}
	return (false);
}

bool check::register_::pwMatch(CmdSpec &cmd, int idx) {
	(void)idx;
	if (cmd[password_][0] != cmd.server_.getPass()) {
		reply::send_(cmd.getSender().getFd(),
					 ERR_PASSWDMISMATCH(cmd.getSender().cliInfo.getNick()));
		return (false);
	}
	return (true);
}

bool check::register_::isRegistered(CmdSpec &cmd, int idx) {
	(void)idx;
	if (cmd.getSender().cliInfo.getRegistration() == 3) {
		reply::send_(cmd.getSender().getFd(),
					 ERR_ALREADYREGISTRED(cmd.getSender().cliInfo.getNick()));
		return (false);
	}
	return (true);
}
