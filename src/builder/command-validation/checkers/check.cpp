/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:15:18 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/31 19:01:42 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.hpp"

bool check::chan(CmdSpec &cmd, int idx) {
	(void)idx;
	stringVec param = cmd[channel_].getInnerParam();
	return (true);
}

bool check::user(CmdSpec &cmd, int idx) {
	(void)idx;
	(void)cmd;
	return (true);
}

bool check::target(CmdSpec &cmd, int idx) {
	(void)cmd;
	(void)idx;
	return (true);
}

bool check::invite(CmdSpec &cmd, int idx) {
	(void)cmd;
	(void)idx;
	return (true);
}

bool check::mess(CmdSpec &cmd, int idx) {
	(void)idx;
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
	size_t i = 0;
	while (i < cmd[target_].size()) {
		if (cmd[target_][i][0] != '#' ||
			(cmd[target_][i][0] != '@' &&
			 (cmd[target_][i].size() > 1 && cmd[target_][i][1] != '#'))) {
			if (!check::target(cmd, i)) {
				cmd[channel_].rmParam(i);
				continue;
			}
		} else {
			if (!check::chan(cmd, i) && !check::chans_::isOnChan(cmd, i)) {
				cmd[channel_].rmParam(i);
				continue;
			}
			if (cmd[target_][i][0] == '@') {
				//TODO: add bool only op et rm le @ s'il est la
			}
		}
		i++;
	}
	if (!cmd[channel_].size())
		return (false);
	return (true);
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
