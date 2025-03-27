/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatMess.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:45:07 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/27 14:16:04 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "formatMess.hpp"
#include "CmdManager.hpp"
#include "Reply.hpp"
#include <algorithm>
#include <sstream>

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */

//TODO: handle single buffer for CAP NICK USER
bool formatMess::assess(Client &sender) {
	std::string message = sender.mess.getBuffer();

	while (!message.empty()) {
		std::string cmd = priv::removeNewlines(message);
		if (cmd.find("CAP") != std::string::npos)
			continue;
		// std::cout << "Extracted	[" + cmd + "]" << std::endl;
		// std::cout << "Remainder	" + message << std::endl;
		if (priv::lenIsValid(cmd, sender) == false)
			return false;
		if (priv::hasPrefix(cmd, sender.cliInfo.getPrefix()) == false)
			return false;
		sender.mess.setCmdParam(vectorSplit(cmd, ' '));
		if (sender.mess.getCmd() == "MODE")
			priv::formatMode(sender);

		CmdManager &manager = CmdManager::getManagerInstance();
		try {
			manager.executeCm(
				manager.findCmd(sender.mess.getCmd()).process(sender));
		} catch (const CmdManager::CmdNotFoundException &e) {
			reply::sendReply(sender.getFd(),
						ERR_UNKNOWNCOMMAND(sender.cliInfo.getNick(),
										   sender.mess.getCmd()));
		}
	}
	return true;
}

stringVec formatMess::vectorSplit(std::string &s, char del) {
	stringVec result;
	std::string token, trailing;

	priv::hasTrailing(s, trailing);
	std::istringstream stream(s);
	while (std::getline(stream, token, del))
		result.push_back(token);
	if (!trailing.empty())
		result.push_back(trailing);
	return (result);
}

void formatMess::priv::formatMode(Client &sender) {
	stringVec mode = sender.mess.getCmdParam();
	if (mode.size() < 2)
		return;
	stringVec modeFormat;
	std::string flagformat, paramformat;

	modeFormat.push_back(mode.at(0));
	modeFormat.push_back(mode.at(1));

	for (stringVec::iterator i = mode.begin() + 2; i != mode.end(); ++i) {
		if (!i->empty()) {
			const char firstChar = (*i)[0];
			if (firstChar == '+' || firstChar == '-') {
				std::string flags = *i;
				for (size_t j = 1; j < flags.size(); ++j) {
					flagformat += firstChar;
					flagformat += (*i)[j];
					flagformat += ' ';
				}
			} else {
				paramformat += *i;
				paramformat += ' ';
			}
		}
	}
	if (!flagformat.empty())
		modeFormat.push_back(flagformat);
	if (!paramformat.empty())
		modeFormat.push_back(paramformat);
	sender.mess.clearCmdParam();
	sender.mess.setCmdParam(modeFormat);
}

bool formatMess::priv::hasPrefix(std::string &mess,
								 const std::string &cliPrefix) {
	if (mess.at(0) == ':') {
		std::string::size_type sep = mess.find(" ");
		if (sep != std::string::npos) {
			std::string prefix = mess.substr(1, (sep - 1));
			if (prefix != cliPrefix)
				return false;
			else
				mess.erase(0, (sep + 1));
		}
	}
	return true;
}

bool formatMess::priv::hasTrailing(std::string &mess, std::string &trailing) {
	std::string::size_type trail = mess.find(" :");

	if (trail != std::string::npos) {
		trailing = mess.substr((trail), mess.size());
		mess.erase(trail);
		return true;
	}
	return false;
}

bool formatMess::priv::lenIsValid(const std::string &mess,
								  const Client &sender) {
	if (mess.empty())
		return false;
	if (mess.size() > 512) {
		reply::sendReply(sender.getFd(), ERR_INPUTTOOLONG(sender.cliInfo.getNick()));
		return false;
	}
	return true;
}

std::string::size_type
formatMess::priv::evaluateTermination(const std::string &mess) {
	if (mess.find("\r\n") != std::string::npos)
		return 2;
	if (mess.find("\n") != std::string::npos)
		return 1;
	return std::string::npos;
}

std::string formatMess::priv::removeNewlines(std::string &mess) {

	std::string::size_type termSize = evaluateTermination(mess);
	if (termSize == std::string::npos) {
		mess.clear();
		return mess;
	}
	std::string::size_type newline =
		(termSize == 2 ? mess.find("\r\n") : mess.find("\n"));
	std::string result = mess.substr(0, newline);
	mess.erase(mess.begin(), (mess.begin() + newline + termSize));
	return result;
}