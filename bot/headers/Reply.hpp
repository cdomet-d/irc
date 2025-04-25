/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:23:33 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/25 10:25:06 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLY_HPP
#define REPLY_HPP

#include <string>

namespace RPL {
	enum e_level { INFO, ERROR, DEBUG, REPLY, GOT };
	void log(e_level level, std::string message, std::string verbose);
	void log(e_level level, std::string message);
	void send_(int fd, std::string reply);

} // namespace RPL

#define BOT "ft-friend"
#define BOTCHAN "where-friends"

#define ERR_NICKINUSE "433"
#define RPL_ENDOFMOTD "376"
#define ERR_CHANOPRIVSNEEDED "482"

#define ERR_INVALIDSYNTAX(target, login)                                       \
	"PRIVMSG " + target + " :invalid syntax: should be !<[a - z]>, is " +      \
		login + "\r\n"
#define ERR_SOMETHINGWENTWRONT(target)                                         \
	"PRIVMSG " + target +                                                      \
		" :something went wrong on our side. Check the bot log!\r\n"
#define ERR_LOGINTOOLONG(target)                                               \
	"PRIVMSG " + target + " :login too long; max is 9 characters.\r\n"
#define ERR_TOOLONG(target) "PRIVSMG " + target + " :len should be < 9\r\n"
#define ERR_CANNOTCREATECHAN                                                   \
	":Someone stole my channel ! I can't work in these conditions >:(\r\n"
#define ERR_CANNOTREGISTER ":My nickname is already in use :(\r\n"

#define RPL_SUCCESS(target) "PRIVMSG " + target + " :attempting to fetch...\r\n"
#define ERR_NOLOCATION(target, login)                                          \
	"PRIVMSG " + target + " :Location not found for " + login + "\r\n"
#define ERR_NOSUCHLOGIN(target, login)                                         \
	"PRIVMSG " + target + " :No such login: " + login + "\r\n"
#define RPL_LOCATION(target, location)                                         \
	"PRIVMSG " + target + " :" + location + "\r\n"

#define KICK(nick)                                                             \
	"KICK #where-friends " + nick + " :Bot is leaving; closing the channel.\r\n"
#define TOPIC "TOPIC #where-friends : do !man to see how to invoke me!\r\n"
#define JOIN(target) "JOIN " + target + "\r\n"
#define REGISTER "PASS 0\r\nNICK ft-friend\r\nUSER ftfriend 0 * :ftircbot\r\n"
#define QUIT "QUIT\r\n"
#define MAN(target)                                                            \
	"PRIVMSG " + target +                                                      \
		" :Invoke me with <!login> to see where your friends are "             \
		"seated. You can also /invite me to your channel, and /kick me "       \
		"from "                                                                \
		"it. If you want me to leave the server, just /msg me with <bye>. "    \
		"I "                                                                   \
		"will close my channel and disconnect from the server.\r\n"

#endif