/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mess.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:42:41 by csweetin          #+#    #+#             */
/*   Updated: 2025/04/03 15:59:36 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.hpp"

bool check::mess(CmdSpec &cmd, int idx) {
	(void)idx;
	if (!check::mess_::params(cmd))
		return (false);

	size_t i = 0;
	while (i < cmd[target_].size()) {
		if (!check::target(cmd, i)) {
			cmd[target_].rmParam(i);
			continue;
		}
		i++;
	}
	if (!cmd[target_].size())
		return (false);
	return (true);
}

bool check::mess_::params(CmdSpec &cmd) {
	if (cmd[target_].empty()) {
		reply::send_(
			cmd.getSender().getFd(),
			ERR_NORECIPIENT(cmd.getSender().cliInfo.getNick(), cmd.getName()));
		return (false);
	}
	if (cmd[message_].empty()) {
		reply::send_(cmd.getSender().getFd(),
					 ERR_NOTEXTTOSEND(cmd.getSender().cliInfo.getNick()));
		return (false);
	}
	return (true);
}
