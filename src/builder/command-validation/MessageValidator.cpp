/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageValidator.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:45:07 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/12 14:30:32 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MessageValidator.hpp"
#include "Reply.hpp"
#include <algorithm>
#include <iostream>

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */

bool MessageValidator::assess(Client &sender) {
	sender.setBuffer(removeNewlines(sender.getBuffer()));
	std::string message = sender.getBuffer();
	std::string trailing;
	std::cout << "[" + message + "]" << std::endl;
	if (lenIsValid(message, sender) == false)
		return false;
	if (hasPrefix(message, sender.getPrefix()) == false)
		return false;
	if (hasTrailing(message, trailing) == false)
		return false;
	sender.setCmdParam(vectorSplit(message, " "));
	sender.setTrailingParam(trailing);
	printCmdParam(sender.getCmdParam());
	return true;
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
		sendReply(sender.getFd(), sender.getNick());
		return false;
	}
	return true;
}

stringVec MessageValidator::vectorSplit(std::string &s,
										const std::string &del) {
	stringVec inputCli;
	size_t pos = 0;
	std::string token;

	while ((pos = s.find(del)) != std::string::npos) {
		token = s.substr(0, pos);
		inputCli.push_back(token);
		s.erase(0, pos + del.length());
	}
	inputCli.push_back(s);
	return (inputCli);
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
	for (stringVec::const_iterator it = obj.begin(); it != obj.end(); ++it)
		std::cout << *it << std::endl;
}