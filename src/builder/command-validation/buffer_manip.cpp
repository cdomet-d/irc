/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_manip.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:45:07 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/28 14:01:53 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer_manip.hpp"
#include "CmdManager.hpp"
#include "Reply.hpp"
#include "printers.hpp"
#include <sstream>

bool buffer_manip::prepareCommand(Client &sender) {
	sender.mess.trimSpaces();
	while (!sender.mess.emptyBuff()) {
		sender.mess.removeNewlines();
		if (sender.mess.isCap()) {
			sender.mess.updateMess();
			continue;
		}
		if (!sender.mess.lenIsValid(sender))
			return false;
		if (sender.mess.hasPrefix(sender.cliInfo.getPrefix()) == false)
			return false;
		sender.mess.hasTrailing();
		std::string buffer = sender.mess.getMess();
		sender.mess.setCmdParam(vectorSplit(buffer, ' '));
		if (sender.mess.getCmd() == "MODE")
			sender.mess.formatMode();
		CmdManager &manager = CmdManager::getManagerInstance();
		try {
			if (sender.mess.getCmd() == "QUIT") {
				manager.executeCm(
					manager.findCmd(sender.mess.getCmd()).process(sender));
				return true;
			}
			manager.executeCm(
				manager.findCmd(sender.mess.getCmd()).process(sender));

		} catch (const CmdManager::CmdNotFoundException &e) {
			reply::send_(sender.getFd(),
						 ERR_UNKNOWNCOMMAND(sender.cliInfo.getNick(),
											sender.mess.getCmd()));
		}
		sender.mess.updateMess();
	}
	return true;
}

stringVec buffer_manip::vectorSplit(std::string &s, char del) {
	stringVec result;
	std::string token, trailing;

	std::istringstream stream(s);
	while (std::getline(stream, token, del))
		result.push_back(token);
	return (result);
}
