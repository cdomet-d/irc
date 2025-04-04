/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_nick.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:23:00 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/03 15:59:36 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.hpp"

bool check::nick(CmdSpec &cmd, int idx) {
	(void)idx;
	if (cmd[nickname_].empty()) {
		reply::send_(cmd.getSender().getFd(),
					 ERR_NONICKNAMEGIVEN(cmd.getSender().cliInfo.getNick()));
		return (false);
	}
	std::string nick = cmd[nickname_][0];
	if (nick.size() > 9) {
		nick = check::nick_::trim(nick);
		cmd[nickname_].rmParam(0);
		cmd[nickname_].setOneParam(nick);
	}
	if (!check::nick_::syntaxIsValid(nick, cmd.getSender()))
		return false;
	if (!check::nick_::isUnique(nick, cmd.server_.getUsedNick(),
								cmd.getSender()))
		return false;
	return true;
}

//TODO: why are we passing nick in param here ?
bool check::nick_::syntaxIsValid(const std::string &nick,
								 const Client &sender) {
	std::string badFirst(": illegal first char (should be a letter), is "),
		illegal(
			": illegal char (should be a letter, a digit or -[]\\`^{}), is ");
	std::string::const_iterator start = nick.begin();

	if (!isalpha(*start)) {
		reply::send_(sender.getFd(),
					 ERR_ERRONEUSNICKNAME(sender.cliInfo.getNick(),
										  nick + badFirst + *start));
		return false;
	}
	start += 1;
	while (start != nick.end()) {
		if (!check::nick_::isAllowed(*start)) {
			reply::send_(sender.getFd(),
						 ERR_ERRONEUSNICKNAME(sender.cliInfo.getNick(),
											  nick + illegal + *start));
			return false;
		}
		++start;
	}
	return true;
}

std::string check::nick_::trim(const std::string &nick) {
	return nick.substr(0, 9);
}

bool check::nick_::isAllowed(const char &c) {
	return isalpha(c) || isdigit(c) || check::nick_::isSpecial(c);
}

bool check::nick_::isSpecial(const char &c) {
	std::string special = "-[]\\`^{}";
	std::string::size_type pos = special.find(c);
	if (pos == std::string::npos)
		return false;
	return true;
}

bool check::nick_::isUnique(const std::string &nick, const nickMap &regCli,
							const Client &sender) {
	// std::cout << "IsUnique" << std::endl;
	nickMap::const_iterator unique = regCli.find(nick);
	if (unique == regCli.end()) {
		// std::cout << "No match found: nick is unique" << std::endl;
		return true;
	}
	// std::cout << "A match found: nick is not unique" << std::endl;
	reply::send_(sender.getFd(), ERR_NICKNAMEINUSE(sender.cliInfo.getNick(), nick));
	return false;
}