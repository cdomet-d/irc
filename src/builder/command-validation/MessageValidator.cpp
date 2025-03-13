/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageValidator.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:45:07 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/13 15:06:37 by cdomet-d         ###   ########.fr       */
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

bool MessageValidator::assess(Client &sender) {
	sender.mess.setBuffer(removeNewlines(sender.mess.getBuffer()));
	std::string message = sender.mess.getBuffer();
	std::string trailing;

	std::cout << "Message	[" + message + "]" << std::endl;
	if (lenIsValid(message, sender) == false)
		return false;
	if (hasPrefix(message, sender.cliInfo.getPrefix()) == false)
		return false;
	hasTrailing(message, trailing);
	sender.mess.setCmdParam(vectorSplit(message, ' '));
	if (!trailing.empty())
		sender.mess.setTrailingParam(trailing);
	if (sender.mess.getCmd() == "MODE")
		formatMode(sender.mess.getCmdParam());

	CmdManager &manager = CmdManager::getManagerInstance(); //TODO issue : cmd MODE is empty
	try {
		manager.executeCm(manager.getCmd(sender.mess.getCmd()).process(sender));
	} catch (const CmdManager::CmdNotFoundException &e) {
		std::cout << ERR_UNKNOWNCOMMAND(sender.cliInfo.getNick(),
										sender.mess.getCmd());
	}
	return true;
}

void MessageValidator::formatMode(stringVec &mode) {

	if (mode.size() < 2)
		return;
	stringVec modeFormat(4);
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
	mode = modeFormat;
}

bool MessageValidator::hasPrefix(std::string &mess,
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

bool MessageValidator::hasTrailing(std::string &mess, std::string &trailing) {
	std::string::size_type trail = mess.find(" :");

	if (trail != std::string::npos) {
		std::cout << "[" + mess.substr((trail + 1), mess.size()) + "]"
				  << std::endl;
		trailing = mess.substr((trail + 1), mess.size());
		mess.erase(trail);
		std::string::size_type trim = trailing.find(':');
		if (trim != std::string::npos)
			trailing.erase(trim, 1);
		return true;
	}
	return false;
}

bool MessageValidator::lenIsValid(const std::string &mess,
								  const Client &sender) {
	if (mess.empty())
		return false;
	if (mess.size() > 512) {
		sendReply(sender.getFd(), sender.cliInfo.getNick());
		return false;
	}
	return true;
}

stringVec MessageValidator::vectorSplit(std::string &s, char del) {
	stringVec result;
	std::string token;
	std::istringstream stream(s);

	while (std::getline(stream, token, del)) {
		result.push_back(token);
	}
	return (result);
}

std::string MessageValidator::removeNewlines(const std::string &input) {
	std::string result;
	for (size_t i = 0; i < input.length(); ++i) {
		if (input[i] != '\r' && input[i] != '\n') {
			result += input[i];
		}
	}
	return result;
}

void MessageValidator::printCmdParam(const stringVec &obj) {
	std::cout << "Print:" << std::endl;
	for (stringVec::const_iterator it = obj.begin(); it != obj.end(); ++it)
		std::cout << *it << std::endl;
}