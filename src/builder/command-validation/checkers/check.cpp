/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:15:18 by csweetin          #+#    #+#             */
/*   Updated: 2025/04/04 13:23:42 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printers.hpp"
#include "validator.hpp"

/* checks that username syntax is valid */
bool check::user(CmdSpec &cmd, int idx) {
	(void)idx;
	(void)cmd;
	return true;
}

/* check that the target exists */
bool check::target(CmdSpec &cmd, int idx) {
	if (!check::exists(cmd[target_][idx], cmd.serv_.getUsedNick())) {
		reply::send_(cmd.getSender().getFd(),
					 ERR_NOSUCHNICK(cmd.getSender().cliInfo.getNick()));
		return false;
	}
	return true;
}

/* check that the target is not already on the chan */
bool check::invite(CmdSpec &cmd, int idx) {
	if (!check::target(cmd, idx))
		return false;
	int targetFd = cmd.serv_.getFdFromNick(cmd[target_][idx]);
	const stringVec &targetChan =
		cmd.serv_.getAllCli().find(targetFd)->second->getJoinedChans();

	if (check::chans_::onChan(cmd[channel_][idx], targetChan)) {
		reply::send_(cmd.getSender().getFd(),
					 ERR_USERONCHANNEL(cmd.getSender().cliInfo.getNick(),
									   cmd[channel_][idx]));
		return false;
	}
	return true;
}

bool check::enoughParams(CmdSpec &cmd, int idx) {
	(void)idx;
	for (size_t i = 0; i < cmd.getParams().size(); i++) {
		CmdParam &innerParam = *cmd.getParams()[i].second;
		if (!innerParam.isOpt() && innerParam.empty()) {
			reply::send_(cmd.getSender().getFd(),
						 ERR_NEEDMOREPARAMS(cmd.getSender().cliInfo.getNick(),
											cmd.getName()));
			return (false);
		}
	}
	return (true);
}
