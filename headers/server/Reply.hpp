/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/07 18:23:12 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef REPLY_H
#define REPLY_H
#include <cstring>
#include <string>

//STANDARD_REPLIES

//ERR_REPLIES
//channel_err_replies
#define ERR_BADCHANNELKEY(nickname, channel) (":irc.bitchat.net 475 " + nickname + " " + channel + " :Cannot join channel (+k)" + "\r\n")
#define ERR_CHANNELISFULL(nickname, channel) (":irc.bitchat.net 471 " + nickname + " " + channel + " :Cannot join channel (+l)\r\n")
#define ERR_CHANOPRIVSNEEDED(nickname, channel)  (":irc.bitchat.net 482 " + nickname + " " + channel + " :You're not channel operator" + "\r\n")
#define ERR_INVITEONLYCHAN(nickname, channel) (":irc.bitchat.net 473 " + nickname  + " " + channel + " :Cannot join channel (+i)\r\n")
#define ERR_TOOMANYCHANNELS(nickname, channel) (":irc.bitchat.net 405 " + nickname + " " + channel + " :You have joined too many channels\r\n")
#define ERR_NOSUCHCHANNEL(nickname, channel) (":irc.bitchat.net 403 " + nickname + " " + channel + " :No such channel" + "\r\n")
#define ERR_NOTONCHANNEL(nickname, channel) (":irc.bitchat.net 442 " + nickname + " " + channel + " :You're not on that channel" + "\r\n")
#define ERR_USERNOTINCHANNEL(nickname, target, channel) (":irc.bitchat.net 441 " + nickname + " " + target + " " + channel + " :They aren't on that channel\r\n")
#define ERR_USERONCHANNEL(nickname, target, channel) (":irc.bitchat.net 443 " + nickname + " " + target + " " + channel + " :is already on channel\r\n")
#define ERR_CANNOTSENDTOCHAN(nickname, channel) (":irc.bitchat.net 404 " + nickname + " " + channel + " :Cannot send to channel\r\n") //TODO : not used

//input_err_replies
#define ERR_NORECIPIENT(nickname, command) (":irc.bitchat.net 411 " + nickname + " :No recipient given (" + command + ")\r\n")
#define ERR_NOTEXTTOSEND(nickname) (":irc.bitchat.net 412 " + nickname + " :No text to send\r\n")
#define ERR_INPUTTOOLONG(nickname) (":irc.bitchat.net 417 " + nickname + " :Input line was too long\r\n")
#define ERR_UNKNOWNCOMMAND(nickname, command) (":irc.bitchat.net 421 " + nickname + " " + command + " :Unknown command\r\n")
#define ERR_NONICKNAMEGIVEN(nickname) (":irc.bitchat.net 431 " + nickname + " :No nickname given\r\n")
#define ERR_ERRONEUSNICKNAME(nickname, newNick) (":irc.bitchat.net 432 " + nickname + " " + newNick + " :Erroneous nickname\r\n")
#define ERR_NEEDMOREPARAMS(nickname, command)(":irc.bitchat.net 461 " + nickname + " " + command + " :Not enough parameters\r\n")
#define ERR_UNKNOWNMODE(nickname, modechar) (":irc.bitchat.net 472 " + nickname + " " + modechar + " :is unknown mode char to me" + "\r\n")
#define ERR_TOOMANYTARGETS(nickname, target) (":irc.bitchat.net 407 " + nickname + " " + target + " :Too many targets\r\n") //TODO : not used

//registration_err_replies
#define ERR_NICKNAMEINUSE(nickname, newNick) (":irc.bitchat.net 433 " + nickname + " " + newNick + " :Nickname is already in use\r\n")
#define ERR_NOTREGISTERED(nickname) (":irc.bitchat.net 451 " + nickname + " :You have not registered\r\n")
#define ERR_ALREADYREGISTRED(nickname) (":irc.bitchat.net 462 " + nickname + " :You may not reregister\r\n")
#define ERR_PASSWDMISMATCH(nickname) (":irc.bitchat.net 464 " + nickname + " :Password incorrect\r\n")
#define ERR_NOSUCHNICK(nickname, target) (":irc.bitchat.net 401 " + nickname + " " + target + " :No such nick/channel\r\n")
#define ERR_NEEDPASS(nickname) (":irc.bitchat.net NOTICE " + nickname + " :Please enter password\r\n")
#define ERR_NEEDNICK(nickname) (":irc.bitchat.net NOTICE " + nickname + " :Please enter nickname\r\n")
#define ERR_NEEDUSER(nickname) (":irc.bitchat.net NOTICE " + nickname + " :Please enter username\r\n")
#define ERR_NEEDNICKORUSER(nickname) (":irc.bitchat.net NOTICE " + nickname + " :Please enter nickname or username\r\n")

//RESPONDS_REPLIES
//serv_replies
#define RPL_WELCOME(nickname, prefix) (":irc.bitchat.net 001 " + nickname + " :Welcome to the Internet Relay Network " + prefix + "\r\n")
#define RPL_YOURHOST(nickname) (":irc.bitchat.net 002 " + nickname + " :Your host is Bitchat, running version 1.0 \r\n")
#define RPL_CREATED(nickname, date) (":irc.bitchat.net 003 " + nickname + " :This server was created " + date + "\r\n") //TODO : not used
#define RPL_MYINFO(nickname) (":irc.bitchat.net 004 " + nickname + " Bitchat 1.0 o klit klo Bitchat IRC | Modes: o,k,l,i,t | Max nick: 9 chars\r\n") //TODO : not used
//TODO: ask where these values come from
#define RPL_ISUPPORT(nickname) ":irc.bitchat.net 005 " + nickname + " Nickname\n CHANMODES=k,l,i,t\n CHANNELLEN=200\n NICKLEN=9\n MAXTARGETS=1\n TOPICLEN=307\n KICKLEN=307\n MODES\n NETWORK=YourNetwork :are supported by this server\r\n"

//channel_replies
#define RPL_CHANNELMODEIS(nickname, channel, modes) (":irc.bitchat.net 324 " + nickname + " " + channel + " " + modes + "\r\n")
#define RPL_ENDOFNAMES(nickname, channel) (":irc.bitchat.net 366 " + nickname + " " + channel + " :End of /NAMES list\r\n")
#define RPL_INVITING(nickname, channel, target) (":irc.bitchat.net 341 " + nickname + " " + channel + " " + target + "\r\n")
#define RPL_NOTOPIC(nickname, channel) (":irc.bitchat.net 331 " + nickname + " " + channel + " :No topic is set" + "\r\n")
#define RPL_TOPIC(nickname, channel, topic) (":irc.bitchat.net 332 " + nickname + " " + channel + " :" + topic + "\r\n")

//client_replies
#define RPL_NAMREPLY(nickname, channel_type, channel, nicks) (":irc.bitchat.net 353 " + nickname + " " + channel_type + " " + channel + " :" + nicks + "\r\n")
#define RPL_UMODEIS(nickname, modes) (":irc.bitchat.net 221 " + nickname + " " + modes + "\r\n") //TODO : not used
#define RPL_AWAY(nickname, message) (":irc.bitchat.net 301 " + nickname + " :" + message + "\r\n") //TODO : not used
#define RPL_INVITELIST(nickname, channel) (":irc.bitchat.net 336 " + nickname + " " + channel + "\r\n")
#define RPL_ENDOFINVITELIST(nickname) (":irc.bitchat.net 337 " + nickname + " :End of invite list\r\n")
#define RPL_MODE(source, channel, modes) (source + " MODE " + channel + " " + modes + "\r\n")

//USER_DEFINED_REPLIES
//notice_replies (uses nickname)
#define NOTICE_REQUIRE_PASSWORD(nickname) (":irc.bitchat.net NOTICE " + nickname + " :You must provide a password using the PASS command before registration\r\n")
#define PASS_SUCCESS(nickname) (":irc.bitchat.net NOTICE " + nickname + " :Valid password ! You may register\r\n")
#define RPL_NICK(nickname) (":irc.bitchat.net NOTICE " + nickname + " :The nickname is valid and saved !\r\n")
#define RPL_USER(nickname, username) (":irc.bitchat.net NOTICE " + nickname + " :The Username " + username + " is valid and saved !\r\n")
#define REG_COMPLETE(nickname) (":irc.bitchat.net NOTICE " + nickname + " :Registration completed, you can join channels and start chatting !\r\n")
#define RPL_CHANOPE(nickname, channel) (":irc.bitchat.net NOTICE " + nickname + " :You're operator of " + channel + "\r\n")
#define RPL_CHANOPENOPE(nickname, channel) (":irc.bitchat.net NOTICE " + nickname + " : You're no longer operator of " + channel + "\r\n")
#define RPL_BYEYBE(nickname) (":irc.bitchat.net " + nickname + " :You quitted the server, see you next time !\r\n")
//command_replies (uses prefix)
#define RPL_INVITE(prefix, target, channel) (":" + prefix + " INVITE " + target + " :" + channel + "\r\n")
#define RPL_JOIN(prefix, channel) (":" + prefix + " JOIN " + channel + "\r\n")
#define RPL_KICK(prefix, channel, target, reason) (":" + prefix + " KICK " + channel + " " + target + " " + reason + "\r\n")
#define RPL_PARTNOREASON(prefix, channel) (":" + prefix + " PART " + channel + "\r\n")
#define RPL_PARTREASON(prefix, channel, reason) (":" + prefix + " PART " + channel + " " + reason + "\r\n")
#define RPL_PRIVMSG(prefix, target, message) (":" + prefix + " PRIVMSG " + target + " " + message + "\r\n")
#define RPL_TOPICCHANGED(prefix, channel, topic) (":" + prefix + " TOPIC " + channel + " :" + topic + "\r\n")
#define RPL_CHANGEMODE(prefix, channel, mode) (":" + prefix + " MODE " + channel + " " + mode + "\r\n") //TODO : not used

namespace reply {
	enum e_level { INFO, ERROR, DEBUG, REPLY };
	void log(e_level level, std::string message, std::string verbose);
	void log(e_level level, std::string message);
	void send_(int fd, std::string reply);

} // namespace reply
#endif //REPLY_HPP
