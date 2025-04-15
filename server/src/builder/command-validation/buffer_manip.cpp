/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_manip.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:45:07 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/15 11:54:17 by aljulien         ###   ########.fr       */
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
		if (sender.mess.getCmd() == "MODE" || sender.mess.getCmd() == "mode")
			sender.mess.formatMode();
		CmdManager &manager = CmdManager::getManagerInstance();
		try {
			if (manager.executeCm(
					manager.findCmd(sender.mess.getCmd()).process(sender)))
				return true;
		} catch (const CmdManager::CmdNotFoundException &e) {
			RPL::send_(sender.getFd(),
					   ERR_UNKNOWNCOMMAND(sender.cliInfo.getNick(),
										  sender.mess.getCmd()));
		}
		//TODO: bit worried that trailing will remain hanging around if the command is not found
		sender.mess.clear();
		sender.mess.updateMess();
	}
	return true;
}

stringVec buffer_manip::vectorSplit(std::string &s, char del) {
	stringVec result;
	std::string token;

	std::istringstream stream(s);
	while (std::getline(stream, token, del))
		result.push_back(token);
	return (result);
}
