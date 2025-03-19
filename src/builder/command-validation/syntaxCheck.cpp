/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxCheck.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:08:53 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/18 16:41:09 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntaxCheck.hpp"
#include "Checkers.hpp"
#include "Reply.hpp"

bool syntaxCheck::nick::isValid(const std::string &nick, const CmdSpec &cmd) {
	std::string badFirst(": illegal first char (should be a letter), is "),
		illegal(
			": illegal char (should be a letter, a digit or -[]\\`^{}), is ");
	std::string::const_iterator start = nick.begin();

	if (!isalpha(*start)) {
		reply::send(cmd.getSender().getFd(),
				  ERR_ERRONEUSNICKNAME(nick + badFirst + *start));
		return false;
	}
	start += 1;
	while (start != nick.end()) {
		if (!syntaxCheck::nick::priv::isValidChar(*start)) {
			reply::send(cmd.getSender().getFd(),
					  ERR_ERRONEUSNICKNAME(nick + illegal + *start));
			return false;
		}
		++start;
	}
	return true;
}

std::string syntaxCheck::nick::trim(const std::string &nick) {
	return nick.substr(0, 9);
}

bool syntaxCheck::nick::priv::isValidChar(const char &c) {
	return isalpha(c) || isdigit(c) || priv::isSpecial(c);
}

bool syntaxCheck::nick::priv::isSpecial(const char &c) {
	std::string special = "-[]\\`^{}";
	std::string::size_type isSpecial = special.find(c);
	if (isSpecial == std::string::npos)
		return false;
	return true;
}

bool conflictCheck::nick::inUse(const std::string &nick,
								const nickMap &regCli, const int &senderFd) {
	nickMap::const_iterator inUse = regCli.find(nick);
	if (inUse == regCli.end())
		return false;
	reply::send(senderFd, ERR_NICKNAMEINUSE(nick));
	return true;
}