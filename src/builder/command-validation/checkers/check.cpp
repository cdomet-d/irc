/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:15:18 by csweetin          #+#    #+#             */
/*   Updated: 2025/04/02 14:22:50 by aljulien         ###   ########.fr       */
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
