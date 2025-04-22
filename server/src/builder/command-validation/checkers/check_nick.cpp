/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_nick.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:23:00 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/22 16:47:40 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.hpp"

bool check::nick(CmdSpec &cmd, size_t idx) {
	if (cmd[nickname_].empty() || cmd[nickname_][0].empty()) {
		RPL::send_(cmd.getSdFd(), ERR_NONICKNAMEGIVEN(cmd.getSdNick()));
		return (false);
	}
	std::string &nick = cmd[nickname_][idx];
	if (!check::nick_::syntaxIsValid(nick, cmd.getSender()))
		return false;
	if (check::exists(nick, cmd.serv_.getUsedNick())) {
		RPL::send_(cmd.getSdFd(), ERR_NICKNAMEINUSE(cmd.getSdNick(), nick));
		return false;
	}
	return true;
}

bool check::nick_::syntaxIsValid(const std::string &nick,
								 const Client &sender) {
	std::string badFirst(": illegal first char: expected [AZ - az], is "),
		illegal(
			": illegal char: expected [AZ - az], [0 - 9] or [-[]\\`^{}], is ");

	std::string::const_iterator start = nick.begin();
	if (!std::isalpha(*start)) {
		RPL::send_(sender.getFd(),
				   ERR_ERRONEUSNICKNAME(sender.cliInfo.getNick(),
										nick + badFirst + *start));
		return false;
	}
	start += 1;
	while (start != nick.end()) {
		if (!check::nick_::isAllowed(*start)) {
			RPL::send_(sender.getFd(),
					   ERR_ERRONEUSNICKNAME(sender.cliInfo.getNick(),
											nick + illegal + *start));
			return false;
		}
		++start;
	}
	return true;
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
