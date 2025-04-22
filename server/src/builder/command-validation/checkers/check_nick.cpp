/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_nick.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:23:00 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/22 18:53:33 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.hpp"

bool check::nick(CmdSpec &cmd, size_t idx) {
	if (cmd[nickname_].empty() || cmd[nickname_][0].empty()) {
		RPL::send_(cmd.getSdFd(), ERR_NONICKNAMEGIVEN(cmd.getSdNick()));
		return (false);
	}
	std::string &nick = cmd[nickname_][idx];
	int rv = check::nick_::syntaxIsValid(nick);
	if (rv != 0) {
		std::string errorMess = check::nick_::createErrorMess(nick, rv);
		RPL::send_(cmd.getSdFd(),
				   ERR_ERRONEUSNICKNAME(cmd.getSdNick(), errorMess));
		return false;
	}
	if (check::exists(nick, cmd.serv_.getUsedNick())) {
		RPL::send_(cmd.getSdFd(), ERR_NICKNAMEINUSE(cmd.getSdNick(), nick));
		return false;
	}
	return true;
}

int check::nick_::syntaxIsValid(const std::string &nick) {

	std::string::const_iterator start = nick.begin();
	if (!std::isalpha(*start))
		return 1;
	start += 1;
	while (start != nick.end()) {
		if (!check::nick_::isAllowed(*start))
			return std::distance(nick.begin(), start);
		++start;
	}
	return 0;
}

std::string check::nick_::createErrorMess(const std::string &nick, int rv) {
	std::string badFirst(": illegal first char: expected [AZ - az], is "),
			illegal(": illegal char: expected [AZ - az], [0 - 9] or "
					"[-[]\\`^{}], is ");
	std::string errorMess;
	std::string::const_iterator start = nick.begin();
	if (rv == 1)
		errorMess = nick + badFirst + *start;
	else
		errorMess = nick + illegal + *(start + rv);
	return (errorMess);
}


bool check::nick_::isAllowed(const char &c) {
	return std::isalpha(c) || isdigit(c) || check::nick_::isSpecial(c);
}

bool check::nick_::isSpecial(const char &c) {
	std::string special = "-[]\\`^{}";
	std::string::size_type pos = special.find(c);
	if (pos == std::string::npos)
		return false;
	return true;
}
