/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:15:18 by csweetin          #+#    #+#             */
/*   Updated: 2025/04/01 14:32:30 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.hpp"
#include "printers.hpp"

/* checks that channel syntax is valid */
//TODO: remove loop, move to join namespace, rename to join::chanSyntaxIsValid
bool check::chan(CmdSpec &cmd) {
	size_t i = 0;
	print::cmdParam(cmd[channel_].getInnerParam(), "channels");
	while (i < cmd[channel_].size()) {
		if (cmd[channel_][i][0] != '#') {
			std::cout << cmd[channel_][i] << std::endl;
			reply::send_(cmd.getSender().getFd(),
						 ERR_NOSUCHCHANNEL(cmd.getSender().cliInfo.getNick(),
										   cmd[channel_][i]));
			cmd[channel_].rmParam(i);
			continue;
		}
		i++;
	}
	if (!cmd[channel_].size())
		return false;
	return (true);
}

/* checks that channel exists */
// bool check::chan(CmdSpec &cmd) 


/* checks that username syntax is valid */
bool check::user(CmdSpec &cmd) {
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

bool check::targetIsOnChan(CmdSpec &cmd, int idx) {
	(void)cmd;
	(void)idx;
	return (true);
}

bool check::invite(CmdSpec &cmd, int idx) {
	(void)cmd;
	(void)idx;
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
