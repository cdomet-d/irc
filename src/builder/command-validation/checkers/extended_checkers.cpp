/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extended_checkers.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:50:22 by csweetin          #+#    #+#             */
/*   Updated: 2025/04/03 15:50:27 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printers.hpp"
#include "validator.hpp"

bool check::part(CmdSpec &cmd, int idx) {
	(void)idx;
	size_t i = 0;

	while (i < cmd[channel_].size()) {
		if (!check::chan(cmd, i)) {
			cmd[channel_].rmParam(i);
			continue;
		}
		i++;
	}
	print::cmdParam(cmd[channel_].getInnerParam(), "part");
	if (cmd[channel_].empty())
		return (false);
	return (true);
}

bool check::kick(CmdSpec &cmd, int idx) {
	(void)idx;
	size_t i = 0;

	while (i < cmd[target_].size()) {
		if (!check::target(cmd, i) || !check::targetIsOnChan(cmd, i)) {
			cmd[target_].rmParam(i);
			continue;
		}
		i++;
	}
	if (cmd[target_].empty())
		return (false);
	return (true);
}
