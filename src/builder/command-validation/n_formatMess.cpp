/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_formatMess.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:45:07 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/27 17:39:45 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_formatMess.hpp"
#include "CmdManager.hpp"
#include "Reply.hpp"
#include "printers.hpp"
#include <algorithm>
#include <sstream>

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */

//TODO: handle single buffer for CAP NICK USER
bool format_mess::assess(Client &sender) {
	while (!sender.mess.emptyBuff()) {
		sender.mess.removeNewlines();
		if (sender.mess.isCap())
			continue;
		if (!sender.mess.lenIsValid(sender))
			return false;
		if (sender.mess.hasPrefix(sender.cliInfo.getPrefix()) == false)
			return false;
		sender.mess.hasTrailing();
		std::string buffer = sender.mess.getMess();
		sender.mess.setCmdParam(vectorSplit(buffer, ' '));
		print::cmdParam(sender.mess.getCmdParam(), "afterSplit");
		if (sender.mess.getCmd() == "MODE")
			sender.mess.formatMode();
		sender.mess.updateMess();
		CmdManager &manager = CmdManager::getManagerInstance();
		try {
		
			std::cout << sender.mess.getCmd() << std::endl;
			manager.executeCm(
				manager.findCmd(sender.mess.getCmd()).process(sender));

		} catch (const CmdManager::CmdNotFoundException &e) {
			reply::send(sender.getFd(),
						ERR_UNKNOWNCOMMAND(sender.cliInfo.getNick(),
										   sender.mess.getCmd()));
		}
		
	}
	return true;
}

stringVec format_mess::vectorSplit(std::string &s, char del) {
	stringVec result;
	std::string token, trailing;

	std::istringstream stream(s);
	while (std::getline(stream, token, del))
		result.push_back(token);
	return (result);
}

