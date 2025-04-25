/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:23:57 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/25 10:24:11 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"
#include "Bot.hpp"
#include "Reply.hpp"

void cmd::man(Bot &bot, const std::string &target) {
	RPL::send_(bot.getFd(), MAN(target));
}

void cmd::acceptInvite(const int fd, const std::string &target) {
	RPL::send_(fd, "JOIN " + target + "\r\n");
}

void cmd::disconnect(Bot &bot) {
	RPL::send_(bot.getFd(),
			   "PRIVMSG #where-friends :Bye! I'm closing the channel!\r\n");
	for (stringVec::const_iterator it = bot.getMembers().begin();
		 it != bot.getMembers().end(); ++it) {
		if (*it != BOT) {
			RPL::send_(bot.getFd(), KICK(*it));
			sleep(0.5);
		}
	}
	bot.clearMembers();
	bot.setSignal(true);
	RPL::send_(bot.getFd(), QUIT);
}

/* ensures that the leading ! is present; removes leading :! */
bool cmd::parseLogin(std::string &login) {
	if (login.empty() || login.size() > 10 || login.size() < 2)
		return false;
	if (login.at(0) == ':')
		login.erase(login.begin());
	if (login.at(0) != '!')
		return false;
	login.erase(login.begin());
	return true;
}
