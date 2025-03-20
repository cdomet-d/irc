/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageValidator.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:45:07 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/20 13:37:42 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MessageValidator.hpp"
#include "CmdManager.hpp"
#include "Reply.hpp"
#include <algorithm>
#include <sstream>

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */

//TODO: handle single buffer for CAP NICK USER
bool messageValidator::assess(Client &sender) {
	std::string message = sender.mess.getBuffer();

	while (!message.empty()) {
		std::string cmd = priv::removeNewlines(message);
		if (cmd.find("CAP") != std::string::npos)
			continue;
		std::cout << "Extracted	[" + cmd + "]" << std::endl;
		std::cout << "Remainder	" + message << std::endl;
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
			reply::send(sender.getFd(),
					  ERR_UNKNOWNCOMMAND(sender.cliInfo.getNick(),
										 sender.mess.getCmd()));
		}
	}
	return true;
}

stringVec messageValidator::vectorSplit(std::string &s, char del) {
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

void messageValidator::printCmdParam(const stringVec &obj, std::string where) {
	std::cout << "[" << std::endl;
	for (stringVec::const_iterator it = obj.begin(); it != obj.end(); ++it) {
		if ((*it).empty())
			std::cout << "\t" + where + ":\t" << "[...]" << std::endl;
		else
			std::cout << "\t" + where + ":\t" << *it << std::endl;
	}
	std::cout << "]" << std::endl;
}

void messageValidator::priv::formatMode(Client &sender) {
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

bool messageValidator::priv::hasPrefix(std::string &mess,
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

bool messageValidator::priv::hasTrailing(std::string &mess,
										 std::string &trailing) {
	std::string::size_type trail = mess.find(" :");

	if (trail != std::string::npos) {
		trailing = mess.substr((trail), mess.size());
		mess.erase(trail);
		return true;
	}
	return false;
}

bool messageValidator::priv::lenIsValid(const std::string &mess,
										const Client &sender) {
	if (mess.empty())
		return false;
	if (mess.size() > 512) {
		reply::send(sender.getFd(), ERR_INPUTTOOLONG(sender.cliInfo.getNick()));
		return false;
	}
	return true;
}

std::string messageValidator::priv::removeNewlines(std::string &input) {
    std::string result;
    std::string::size_type newline = input.find(MESSAGE_TERMINATION);
    if (newline == std::string::npos) {
        result.assign(input, 0, input.size() - 1);
        input.erase(input.begin(), input.end());
        return (result);
    }
    result = input.substr(0, newline);
    input.erase(input.begin(), (input.begin() + newline + 2));
    return result;
}