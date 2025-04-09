/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_nick.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:23:00 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/09 13:40:37 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.hpp"

bool
check::nick (CmdSpec &cmd, size_t idx) {
	if (cmd[nickname_].empty ()) {
		reply::send_ (cmd.getSendFd (),
					  ERR_NONICKNAMEGIVEN (cmd.getSendNick ()));
		return (false);
	}
	cmd[nickname_].trimParam (idx, NICKLEN);
	std::string &nick = cmd[nickname_][idx];
	if (!check::nick_::syntaxIsValid (nick, cmd.getSender ()))
		return false;
	if (check::exists (nick, cmd.serv_.getUsedNick ())) {
		reply::send_ (cmd.getSendFd (),
					  ERR_NICKNAMEINUSE (cmd.getSendNick (), nick));
		return false;
	}
	return true;
}

// TODO: why are we passing nick in param here ?
bool
check::nick_::syntaxIsValid (const std::string &nick, const Client &sender) {
	std::string badFirst (": illegal first char (should be a letter), is "),
		illegal (
			": illegal char (should be a letter, a digit or -[]\\`^{}), is ");

	std::string::const_iterator start = nick.begin ();
	if (!isalpha (*start)) {
		reply::send_ (sender.getFd (),
					  ERR_ERRONEUSNICKNAME (sender.cliInfo.getNick (),
											nick + badFirst + *start));
		return false;
	}
	start += 1;
	while (start != nick.end ()) {
		if (!check::nick_::isAllowed (*start)) {
			reply::send_ (sender.getFd (),
						  ERR_ERRONEUSNICKNAME (sender.cliInfo.getNick (),
												nick + illegal + *start));
			return false;
		}
		++start;
	}
	return true;
}

bool
check::nick_::isAllowed (const char &c) {
	return isalpha (c) || isdigit (c) || check::nick_::isSpecial (c);
}

bool
check::nick_::isSpecial (const char &c) {
	std::string special = "-[]\\`^{}";
	std::string::size_type pos = special.find (c);
	if (pos == std::string::npos)
		return false;
	return true;
}
