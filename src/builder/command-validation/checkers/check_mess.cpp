/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mess.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:42:41 by csweetin          #+#    #+#             */
/*   Updated: 2025/04/04 17:57:02 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.hpp"

bool check::mess(CmdSpec &cmd, size_t idx) {
	if (!check::mess_::params(cmd))
		return (false);

	while (idx < cmd[target_].size()) {
		if (cmd[target_][idx][0] != '#') {
			if (!check::target(cmd, idx)) {
				cmd[target_].rmParam(idx);
				continue;
			}
		} else if (!check::chan(cmd, idx)) {
			cmd[target_].rmParam(idx);
			continue;
		}
		idx++;
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
