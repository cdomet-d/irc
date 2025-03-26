/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_nick.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:23:00 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/26 14:14:10 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.hpp"

//TODO: move trim to UserInfo.cpp
//TODO: refacto nick to use internal methods

bool check::nick(CmdSpec &cmd) {
	std::string nick = cmd[nickname_][0];
	if (nick.size() > 9) {
		nick = check::nick_::trim(nick);
		cmd[nickname_].rmParam(0);
		cmd[nickname_].setOneParam(nick);
	}
	if (!check::nick_::syntaxCheck(nick, cmd))
		return false;
	if (check::nick_::unique(nick, cmd.server_.getUsedNick(),
								   cmd.getSender().getFd()))
		return false;
	reply::send(cmd.getSender().getFd(),
				cmd[nickname_][0] + " is valid nickname\n");
	return true;
}

//TODO: why are we passing nick in param here ?
bool check::nick_::syntaxCheck(const std::string &nick, const CmdSpec &cmd) {
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
		if (!check::nick_::isAllowedChar(*start)) {
			reply::send(cmd.getSender().getFd(),
					  ERR_ERRONEUSNICKNAME(nick + illegal + *start));
			return false;
		}
		++start;
	}
	return true;
}

std::string check::nick_::trim(const std::string &nick) {
	return nick.substr(0, 9);
}

bool check::nick_::isAllowedChar(const char &c) {
	return isalpha(c) || isdigit(c) || isSpecialChar(c);
}

bool check::nick_::isSpecialChar(const char &c) {
	std::string special = "-[]\\`^{}";
	std::string::size_type pos = special.find(c);
	if (pos == std::string::npos)
		return false;
	return true;
}

bool check::nick_::unique(const std::string &nick,
								const nickMap &regCli, const int &senderFd) {
	nickMap::const_iterator unique = regCli.find(nick);
	if (unique == regCli.end())
		return false;
	reply::send(senderFd, ERR_NICKNAMEINUSE(nick));
	return true;
}