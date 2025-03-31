/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:15:18 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/31 11:43:57 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.hpp"
#include "printers.hpp"

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

bool check::user(CmdSpec &cmd) {
	(void)cmd;
	return (true);
}

bool check::target(CmdSpec &cmd) {
	(void)cmd;
	return (true);
}

bool check::invite(CmdSpec &cmd) {
	(void)cmd;
	return (true);
}

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
