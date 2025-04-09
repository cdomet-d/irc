/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mess.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:42:41 by csweetin          #+#    #+#             */
/*   Updated: 2025/04/09 13:40:37 by cdomet-d         ###   ########.fr       */
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
			cmd.getSendFd(),
			ERR_NORECIPIENT(cmd.getSendNick(), cmd.getName()));
		return (false);
	}
	if (cmd[message_].empty()) {
		reply::send_(cmd.getSendFd(),
					 ERR_NOTEXTTOSEND(cmd.getSendNick()));
		return (false);
	}
	return (true);
}
