/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mess.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:42:41 by csweetin          #+#    #+#             */
/*   Updated: 2025/04/15 11:54:21 by aljulien         ###   ########.fr       */
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
	if (cmd[target_].empty() || cmd[target_][0].empty()) {
		RPL::send_(cmd.getSdFd(),
				   ERR_NORECIPIENT(cmd.getSdNick(), cmd.getName()));
		return (false);
	}
	if (cmd[message_].empty() || cmd[message_][0].empty()) {
		RPL::send_(cmd.getSdFd(), ERR_NOTEXTTOSEND(cmd.getSdNick()));
		return (false);
	}
	return (true);
}
