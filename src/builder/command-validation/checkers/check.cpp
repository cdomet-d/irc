/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:15:18 by csweetin          #+#    #+#             */
/*   Updated: 2025/04/01 08:34:19 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.hpp"

bool check::chan(CmdSpec &cmd) {
	stringVec param = cmd[channel_].getInnerParam();
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
