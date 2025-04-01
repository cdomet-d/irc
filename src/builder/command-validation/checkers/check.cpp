/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:15:18 by csweetin          #+#    #+#             */
/*   Updated: 2025/04/01 10:11:44 by cdomet-d         ###   ########.fr       */
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
	(void)cmd;
	return (true);
}

/* checks that user exists */
bool check::target(CmdSpec &cmd) {
	(void)cmd;
	return (true);
}

/* loops on target list to ensure they exist and are not on the channel */
bool check::invite(CmdSpec &cmd) {
	(void)cmd;
	return (true);
}

/* loops on target list to ensure they exist and are on the channel */
bool check::kick(CmdSpec &cmd) {
	(void)cmd;
	return (true);
}

bool check::mess(CmdSpec &cmd) {
	(void)cmd;
	return (true);
}

bool findString(stringVec array, std::string &strToFind) {
	for (size_t i = 0; i < array.size(); i++) {
		if (array[i] == strToFind)
			return (true);
	}
	return (false);
}
