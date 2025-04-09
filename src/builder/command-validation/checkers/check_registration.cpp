/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_registration.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:45:57 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/09 13:40:37 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.hpp"

bool
check::register_::stageDone (CmdSpec &cmd, size_t idx) {
	(void)idx;
	if (cmd.getSender ().cliInfo.getRegistration ()
			<= cmd.getRegistrationStage ()
		|| cmd.getSender ().cliInfo.getRegistration () == 3)
		return (true);
	if (cmd.getSender ().cliInfo.getRegistration () == 1)
		reply::send_ (cmd.getSendFd (),
					  ERR_NEEDNICKORUSER (cmd.getSendNick ()));
	if (cmd.getSender ().cliInfo.getRegistration () == 2) {
		if (cmd.getSendNick () != "*"
			&& (cmd.getName () == "NICK" || cmd.getName () == "PASS"))
			reply::send_ (cmd.getSendFd (), ERR_NEEDUSER (cmd.getSendNick ()));
		else if (!cmd.getSender ().cliInfo.getUsername ().empty ()
				 && (cmd.getName () == "USER" || cmd.getName () == "PASS"))
			reply::send_ (cmd.getSendFd (), ERR_NEEDNICK (cmd.getSendNick ()));
		else
			return (true);
	}
	return (false);
}

bool
check::register_::pwMatch (CmdSpec &cmd, size_t idx) {
	if (cmd[password_][idx] != cmd.serv_.getPass ()) {
		reply::send_ (cmd.getSendFd (),
					  ERR_PASSWDMISMATCH (cmd.getSendNick ()));
		return (false);
	}
	return (true);
}

bool
check::register_::isRegistered (CmdSpec &cmd, size_t idx) {
	(void)idx;
	if (cmd.getSender ().cliInfo.getRegistration () == 3) {
		reply::send_ (cmd.getSendFd (),
					  ERR_ALREADYREGISTRED (cmd.getSendNick ()));
		return (false);
	}
	return (true);
}
