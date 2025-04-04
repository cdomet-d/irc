/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:15:18 by csweetin          #+#    #+#             */
/*   Updated: 2025/04/04 11:03:33 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printers.hpp"
#include "validator.hpp"

/* checks that username syntax is valid */
bool check::user(CmdSpec &cmd, int idx) {
	(void)idx;
	(void)cmd;
	return (true);
}

/* check that the target exists */
bool check::target(CmdSpec &cmd, int idx) {
	if (!check::exists(cmd[target_][idx], cmd.server_.getUsedNick())) {
		reply::send_(cmd.getSender().getFd(),
					 ERR_NOSUCHNICK(cmd.getSender().cliInfo.getNick()));
		return false;
	}
	return (true);
}

bool check::chan(CmdSpec &cmd, int idx) {
	if (!check::exists(cmd[channel_][idx], cmd.server_.getAllChan())) {
		reply::send_(cmd.getSender().getFd(),
					 ERR_NOSUCHNICK(cmd.getSender().cliInfo.getNick()));
		return false;
	}
	return (true);
}

/* check that the target is on the chan */
bool check::targetIsOnChan(CmdSpec &cmd, int idx) {
	(void)cmd;
	(void)idx;
	return (true);
}

/* check that the target is not already on the chan */
bool check::invite(CmdSpec &cmd, int idx) {
	if (check::chans_::isOnChan(cmd, idx)) {
		reply::send_(cmd.getSender().getFd(),
					 ERR_USERONCHANNEL(cmd.getSender().cliInfo.getNick(), cmd[channel_][idx]));
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

bool check::findString(stringVec array, std::string &strToFind) {
	for (size_t i = 0; i < array.size(); i++) {
		if (array[i] == strToFind)
			return (true);
	}
	return (false);
}
