/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/24 19:26:38 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLY_HPP
# define REPLY_HPP

#include "typedef.hpp"
#include <cstring>
#include <string>

// STANDARD_REPLIES

// ERR_REPLIES
// channel_err_replies
#define ERR_BADCHANNELKEY(nickname, channel)                                   \
	(":irc.bitchat.net 475 " + nickname + " " + channel +                      \
	 " :Cannot join channel (+k) - bad key" + "\r\n")
#define ERR_CHANNELISFULL(nickname, channel)                                   \
	(":irc.bitchat.net 471 " + nickname + " " + channel +                      \
	 " :Cannot join channel (+l) - channel is full, try again later\r\n")
#define ERR_CHANOPRIVSNEEDED(nickname, channel)                                \
	(":irc.bitchat.net 482 " + nickname + " " + channel +                      \
	 " :You're not channel operator" + "\r\n")
#define ERR_INVITEONLYCHAN(nickname, channel)                                  \
	(":irc.bitchat.net 473 " + nickname + " " + channel +                      \
	 " :Cannot join channel (+i) - you must be invited\r\n")
#define ERR_TOOMANYCHANNELS(nickname, channel)                                 \
	(":irc.bitchat.net 405 " + nickname + " " + channel +                      \
	 " :You have joined too many channels\r\n")
#define ERR_NOSUCHCHANNEL(nickname, channel)                                   \
	(":irc.bitchat.net 403 " + nickname + " " + channel +                      \
	 " :No such channel" + "\r\n")
#define ERR_NOTONCHANNEL(nickname, channel)                                    \
	(":irc.bitchat.net 442 " + nickname + " " + channel +                      \
	 " :You're not on that channel" + "\r\n")
#define ERR_USERNOTINCHANNEL(nickname, target, channel)                        \
	(":irc.bitchat.net 441 " + nickname + " " + target + " " + channel +       \
	 " :They aren't on that channel\r\n")
#define ERR_USERONCHANNEL(nickname, target, channel)                           \
	(":irc.bitchat.net 443 " + nickname + " " + target + " " + channel +       \
	 " :is already on channel\r\n")

// input_err_replies
#define ERR_NORECIPIENT(nickname, command)                                     \
	(":irc.bitchat.net 411 " + nickname + " :No recipient given (" + command + \
	 ")\r\n")
#define ERR_NOTEXTTOSEND(nickname)                                             \
	(":irc.bitchat.net 412 " + nickname + " :No text to send\r\n")
#define ERR_INPUTTOOLONG(nickname)                                             \
	(":irc.bitchat.net 417 " + nickname + " :Input line was too long\r\n")
#define ERR_UNKNOWNCOMMAND(nickname, command)                                  \
	(":irc.bitchat.net 421 " + nickname + " " + command +                      \
	 " :Unknown command\r\n")
#define ERR_NONICKNAMEGIVEN(nickname)                                          \
	(":irc.bitchat.net 431 " + nickname + " :No nickname given\r\n")
#define ERR_ERRONEUSNICKNAME(nickname, newNick)                                \
	(":irc.bitchat.net 432 " + nickname + " " + newNick +                      \
	 " :Erroneous nickname\r\n")
#define ERR_ERRONEUSUSERNAME(nickname, username)                               \
	(":irc.bitchat.net NOTICE " + nickname + " " + username +                  \
	 " :Erroneous username\r\n")
#define ERR_NEEDMOREPARAMS(nickname, command)                                  \
	(":irc.bitchat.net 461 " + nickname + " " + command +                      \
	 " :Not enough parameters\r\n")
#define ERR_UNKNOWNMODE(nickname, modechar)                                    \
	(":irc.bitchat.net 472 " + nickname + " " + modechar +                     \
	 " :is unknown mode char to me" + "\r\n")

// registration_err_replies
#define ERR_ALREADYREGISTERED(nickname)                                        \
	(":irc.bitchat.net 462 " + nickname + " :You may not reregister\r\n")
#define ERR_NEEDNICK(nickname)                                                 \
	(":irc.bitchat.net NOTICE " + nickname + " :Please enter nickname\r\n")
#define ERR_NEEDNICKORUSER(nickname)                                           \
	(":irc.bitchat.net NOTICE " + nickname +                                   \
	 " :Please enter nickname or username\r\n")
#define ERR_NEEDPASS(nickname)                                                 \
	(":irc.bitchat.net NOTICE " + nickname + " :Please enter password\r\n")
#define ERR_NEEDUSER(nickname)                                                 \
	(":irc.bitchat.net NOTICE " + nickname + " :Please enter username\r\n")
#define ERR_NICKNAMEINUSE(nickname, newNick)                                   \
	(":irc.bitchat.net 433 " + nickname + " " + newNick +                      \
	 " :Nickname is already in use\r\n")
#define ERR_NOSUCHNICK(nickname, target)                                       \
	(":irc.bitchat.net 401 " + nickname + " " + target +                       \
	 " :No such nick/channel\r\n")
#define ERR_NOTREGISTERED(nickname)                                            \
	(":irc.bitchat.net 451 " + nickname + " :You have not registered\r\n")
#define ERR_PASSWDMISMATCH(nickname)                                           \
	(":irc.bitchat.net 464 " + nickname + " :Incorrect password\r\n")

//serv_replies
#define RPL_WELCOME(nickname, prefix)                                          \
	(":irc.bitchat.net 001 " + nickname +                                      \
	 " :Welcome to the Bitchat Internet Relay Chat Network " + prefix +        \
	 "\r\n")
#define RPL_YOURHOST(nickname)                                                 \
	(":irc.bitchat.net 002 " + nickname +                                      \
	 " :Your host is Bitchat, running version 1.0\r\n")
#define RPL_CREATED(nickname, date)                                            \
	(":irc.bitchat.net 003 " + nickname + " :This server was created " +       \
	 date + "\r\n")
#define RPL_MYINFO(nickname)                                                   \
	(":irc.bitchat.net 004 " + nickname + " Bitchat 1.0 kolit kol\r\n")
#define RPL_ISUPPORT(nickname)                                                 \
	":irc.bitchat.net 005 " + nickname +                                       \
		" CHANLIMIT=#:50 CHANMODES=,ko,l,it CHANTYPES=# CHANNELLEN=200 "       \
		"NICKLEN=9 USERLEN=18  TOPICLEN=307 KICKLEN=307 "                      \
		"TARGMAX=JOIN:,KICK:,PART:,PRIVMSG: "                                  \
		"PREFIX=(o)@ NETWORK=Bitchat :are "                                    \
		"supported by this server\r\n"
#define RPL_MOTDSTART(nickname)                                                \
	(":irc.bitchat.net 375 " + nickname +                                      \
	 " :- Bitchat Message of the day - \r\n")
#define RPL_ENDOFMOTD(nickname)                                                \
	(":irc.bitchat.net 376 " + nickname + " :End of /MOTD command\r\n")
#define RPL_MOTD(nickname)                                                     \
	(":irc.bitchat.net 372 " + nickname +                                      \
	 " :Registration completed, you can join channels and start chatting "     \
	 "!\r\n")

//channel_replies
#define RPL_CHANNELMODEIS(nickname, channel, modes, modeArgs)                  \
	(":irc.bitchat.net 324 " + nickname + " " + channel + " " + modes + " " +  \
	 modeArgs + "\r\n")
#define RPL_INVITING(nickname, channel, target)                                \
	(":irc.bitchat.net 341 " + nickname + " " + channel + " " + target + "\r\n")
#define RPL_NOTOPIC(nickname, channel)                                         \
	(":irc.bitchat.net 331 " + nickname + " " + channel +                      \
	 " :No topic is set" + "\r\n")
#define RPL_TOPIC(nickname, channel, topic)                                    \
	(":irc.bitchat.net 332 " + nickname + " " + channel + " :" + topic + "\r\n")

//client_replies
#define RPL_NAMREPLY(nickname, channel_type, channel, nicks)                   \
	(":irc.bitchat.net 353 " + nickname + " " + channel_type + " " + channel + \
	 " :" + nicks + "\r\n")
#define RPL_ENDOFNAMES(nickname, channel)                                      \
	(":irc.bitchat.net 366 " + nickname + " " + channel +                      \
	 " :End of /NAMES list\r\n")
#define RPL_INVITELIST(nickname, channel)                                      \
	(":irc.bitchat.net 336 " + nickname + " " + channel + "\r\n")
#define RPL_ENDOFINVITELIST(nickname)                                          \
	(":irc.bitchat.net 337 " + nickname + " :End of /INVITE list\r\n")
#define RPL_WHOREPLY(nickname, channel, username, host, flag, realname)        \
	(":irc.bitchat.net 352 " + nickname + " " + channel + " " + username +     \
	 " " + host + " irc.bitchat.net " + nickname + " " + flag + " :0 " +       \
	 realname + "\r\n")
#define RPL_ENDOFWHO(nickname, channel)                                        \
	(":irc.bitchat.net 315 " + nickname + " " + channel +                      \
	 " :End of /WHO list\r\n")

//USER_DEFINED_REPLIES
//notice_replies (uses nickname)
#define NOTICE_REQUIRE_PASSWORD(nickname)                                      \
	(":irc.bitchat.net NOTICE " + nickname +                                   \
	 " :You must provide a password using the PASS command before "            \
	 "registration\r\n")
#define PASS_SUCCESS(nickname)                                                 \
	(":irc.bitchat.net NOTICE " + nickname +                                   \
	 " :Valid password ! You may register\r\n")
#define RPL_VALIDNICK(nickname)                                                \
	(":irc.bitchat.net NOTICE " + nickname +                                   \
	 " :The nickname is valid and saved !\r\n")
#define RPL_USER(nickname, username)                                           \
	(":irc.bitchat.net NOTICE " + nickname + " :The Username " + username +    \
	 " is valid and saved !\r\n")
#define RPL_CHANOPE(nickname, channel)                                         \
	(":irc.bitchat.net NOTICE " + nickname + " :You're operator of " +         \
	 channel + "\r\n")
#define RPL_CHANOPENOPE(nickname, channel)                                     \
	(":irc.bitchat.net NOTICE " + nickname +                                   \
	 " : You're no longer operator of " + channel + "\r\n")
#define RPL_BYEYBE(nickname)                                                   \
	(":irc.bitchat.net " + nickname +                                          \
	 " :You quitted the server, see you next time !\r\n")
#define RPL_ERROR(host, reason)                                                \
	("ERROR :Closing Link: " + host + " (" + reason + ")\r\n")

//command_replies (uses prefix)
#define ERR_BADKEYLEN(nickname)                                                \
	(":irc.bitchat.net NOTICE " + nickname +                                   \
	 " :Bad key (+k) - key len must be at least 8 and no more than 26\r\n")
#define ERR_BADINPUT(nickname, expected, received)                             \
	(":irc.bitchat.net NOTICE " + nickname + " :format should be [" +          \
	 expected + "], is [" + received + "]\r\n")
#define RPL_INVITE(prefix, target, channel)                                    \
	(":" + prefix + " INVITE " + target + " :" + channel + "\r\n")
#define RPL_JOIN(prefix, channel) (":" + prefix + " JOIN " + channel + "\r\n")
#define RPL_KICK(prefix, channel, target, reason)                              \
	(":" + prefix + " KICK " + channel + " " + target + " " + reason + "\r\n")
#define RPL_PARTNOREASON(prefix, channel)                                      \
	(":" + prefix + " PART " + channel + "\r\n")
#define RPL_PARTREASON(prefix, channel, reason)                                \
	(":" + prefix + " PART " + channel + " " + reason + "\r\n")
#define RPL_PRIVMSG(prefix, target, message)                                   \
	(":" + prefix + " PRIVMSG " + target + " :" + message + "\r\n")
#define RPL_TOPICCHANGED(prefix, channel, Topic)                               \
	(":" + prefix + " TOPIC " + channel + " :" + Topic + "\r\n")
#define RPL_MODE(prefix, channel, Mode, modeArgs)                              \
	(":" + prefix + " MODE " + channel + " " + Mode + " " + modeArgs + "\r\n")
#define RPL_QUIT(prefix, message) (":" + prefix + " QUIT :" + message + "\r\n")
#define RPL_NICK(prefix, newNick) (":" + prefix + " NICK :" + newNick + "\r\n")
#define RPL_PONG(message)                                                      \
	(":irc.bitchat.net PONG irc.bitchat.net :" + message + "\r\n")

namespace RPL {
	enum e_level { INFO, ERROR, DEBUG, REPLY, GOT };
	void log(e_level level, std::string message, std::string verbose);
	void log(e_level level, std::string message);
	void send_(int fd, std::string reply);
	void sendMessageChannel(clientMap allCliChannel,
							const std::string &message);
} // namespace RPL
#endif // REPLY_HPP

