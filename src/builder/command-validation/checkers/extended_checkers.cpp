/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extended_checkers.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:50:22 by csweetin          #+#    #+#             */
/*   Updated: 2025/04/09 14:52:56 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printers.hpp"
#include "validator.hpp"

//TODO: used idx to loop in extended checkers instead of idx;

bool check::part(CmdSpec &cmd, size_t idx) {
	while (idx < cmd[channel_].size()) {
		if (!check::chan(cmd, idx)) {
			cmd[channel_].rmParam(idx);
			continue;
		}
		idx++;
	}
	if (cmd[channel_].empty())
		return (false);
	return (true);
}

bool check::kick(CmdSpec &cmd, size_t idx) {
	while (idx < cmd[target_].size()) {
		const stringVec &tChan =
			check::getTargetChan(cmd[target_][idx], cmd.serv_);
		if (!check::target(cmd, idx)) {
			cmd[target_].rmParam(idx);
			continue;
		}
		if (!check::chans_::onChan(cmd[channel_][0], tChan)) {
			reply::send_(cmd.getSender().getFd(),
						 ERR_USERNOTINCHANNEL(cmd.getSender().cliInfo.getNick(),
											  cmd[target_][idx],
											  cmd[channel_][0]));
			cmd[target_].rmParam(idx);
			continue;
		}
		idx++;
	}
	if (cmd[target_].empty())
		return (false);
	return (true);
}
