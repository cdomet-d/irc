/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:33:33 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/27 11:29:26 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLY_H
#define REPLY_H
#include <cstring>
#include <string>

//STANDARD_REPLIES

//ERR_REPLIES
//channel_err_replies
#define ERR_BADCHANNELKEY(nickname, channel) (":bitchat 475 " + nickname + " " + channel + " :Cannot join channel (+k)" + "\r\n")
#define ERR_CHANNELISFULL(nickname, channel) (":bitchat 471 " + nickname + " " + channel + " :Cannot join channel (+l)\r\n")
#define ERR_CHANOPRIVSNEEDED(nickname, channel)  (":bitchat 482 " + nickname + " " + channel + " :You're not channel operator" + "\r\n")
#define ERR_INVITEONLYCHAN(nickname, channel) (":bitchat 473 " + nickname  + " " + channel + " :Cannot join channel (+i)\r\n")
#define ERR_TOOMANYCHANNELS(nickname, channel) (":bitchat 405 " + nickname + " " + channel + " :You have joined too many channels\r\n")
#define ERR_NOSUCHCHANNEL(nickname, channel) (":bitchat 403 " + nickname + " " + channel + " :No such channel" + "\r\n")
#define ERR_NOTONCHANNEL(nickname, channel) (":bitchat 442 " + nickname + " " + channel + " :You're not on that channel" + "\r\n")
#define ERR_USERNOTINCHANNEL(nickname, channel) (":bitchat 441 " + nickname + " " + channel + " :They aren't on that channel\r\n") //TODO : not used
#define ERR_USERONCHANNEL(nickname, channel) (":bitchat 443 " + nickname + " " + channel + " :is already on channel\r\n") //TODO : not used
#define ERR_CANNOTSENDTOCHAN(nickname, channel) (":bitchat 404 " + nickname + " " + channel + " :Cannot send to channel\r\n") //TODO : not used
//input_err_replies
#define ERR_NORECIPIENT(command) (":bitchat 411 :No recipient given (" + command + ")\r\n")
#define ERR_NOTEXTTOSEND() (":bitchat 412 :No text to send\r\n")
#define ERR_INPUTTOOLONG(nickname) (":bitchat 417 " + nickname + " :Input line was too long\r\n")
#define ERR_UNKNOWNCOMMAND(nickname, command) (":bitchat 421 " + nickname + " " + command + " :Unknown command\r\n")
#define ERR_NONICKNAMEGIVEN() (":bitchat 431 :No nickname given\r\n")
#define ERR_ERRONEUSNICKNAME(newNick) (":bitchat 432 " + newNick + " :Erroneous nickname\r\n")
#define ERR_NEEDMOREPARAMS(nickname, command)(":bitchat 461 " + nickname + " " + command + " :Not enough parameters\r\n")
#define ERR_UNKNOWNMODE(nickname, modechar) (":bitchat 472 " + nickname + " " + modechar + " :is unknown mode char to me" + "\r\n") //TODO : not used
#define ERR_TOOMANYTARGETS(nickname, target) (":bitchat 407 " + nickname + " " + target + " :Too many targets\r\n") //TODO : not used
//registration_err_replies
#define ERR_NICKNAMEINUSE(newNick) (":bitchat 433 " + newNick + " :Nickname is already in use\r\n")
#define ERR_NOTREGISTERED() ":bitchat 451 * :You have not registered\r\n"
#define ERR_ALREADYREGISTRED(nickname) (":bitchat 462 " + nickname + " :You may not reregister\r\n")
#define ERR_PASSWDMISMATCH(nickname) (":bitchat 464 " + nickname + " :Password incorrect\r\n")
#define ERR_NOSUCHNICK(nickname) (":bitchat 401 " + nickname + " :No such nick/channel\r\n") //TODO : not used

//RESPONDS_REPLIES
//server_replies
#define RPL_CREATED(date) (":bitchat 003 :This server was created " + date + "\r\n") //TODO : not used
#define RPL_YOURHOST(servername, version) (":bitchat 002 :Your host is " + servername + ", running version " + version + "\r\n") //TODO : not used
#define RPL_WELCOME(nickname, user, prefix) (":bitchat 001 " + nickname + " :Welcome to the Internet Relay Network " + prefix "\r\n") //TODO : not used
//channel_replies
#define RPL_CHANNELMODEIS(nickname, channel, modes) (":bitchat 324 " + nickname + " " + channel + " :" + modes + "\r\n")
#define RPL_ENDOFNAMES(nickname, channel) (":bitchat 366 " + nickname + " " + channel + " :End of /NAMES list\r\n")
#define RPL_INVITING(nickname, channel, target) (":bitchat 341 " + nickname + " " + channel + " " + target + "\r\n")
#define RPL_NOTOPIC(nickname, channel) (":bitchat 331 " + nickname + " " + channel + " :No topic is set" + "\r\n")
#define RPL_TOPIC(nickname, channel, topic) (":bitchat 332 " + nickname + " " + channel + " " + topic + "\r\n")
//client_replies
#define RPL_NAMREPLY(nickname, channel_type, channel, nicks) (":bitchat 353 " + nickname + " " + channel_type + " " + channel + " :" + nicks + "\r\n")
#define RPL_UMODEIS(nickname, modes) (":bitchat 221 " + nickname + " " + modes + "\r\n")
#define RPL_AWAY(nickname, message) (":bitchat 301 " + nickname + " :" + message + "\r\n") //TODO : not used
#define RPL_MYINFO(servername, version, umodes, cmodes) (":bitchat 004 " + servername + " " + version + " " + umodes + " " + cmodes + "\r\n") //TODO : not used

//USER_DEFINED_REPLIES
//notice_replies (uses nickname)
#define NOTICE_REQUIRE_PASSWORD() (":bitchat NOTICE : You must provide a password using the PASS command before registration\r\n")
#define PASS_SUCCESS() (":bitchat NOTICE : Valid password ! You may register\r\n")
#define RPL_NICK(nickname) (":bitchat NOTICE : The nickname " + nickname + " is valid and saved !\r\n")
#define RPL_USER(username) (":bitchat NOTICE : The Username " + username + " is valid and saved !\r\n")
#define REG_COMPLETE(nickname) (":bitchat NOTICE " + nickname + " : Registration completed, you can join channels and start chatting !\r\n")
#define RPL_CHANOPE(nickname, channel) (":bitchat NOTICE " + nickname + " : You're operator of " + channel + "\r\n")
#define RPL_BYEYBE(nickname) (":bitchat " + nickname + " You quitted the server, see you next time !\r\n")
//command_replies (uses prefix)
#define RPL_INVITE(prefix, target, channel) (":bitchat " + prefix + " INVITE " + target + " :" + channel + "\r\n")
#define RPL_JOIN(prefix, channel) (":bitchat " + prefix + " JOIN :" + channel + "\r\n")
#define RPL_KICK(prefix, channel, target, reason) (":bitchat " + prefix + " KICK " + channel + " " + target + " " + reason + "\r\n")
#define RPL_PARTNOREASON(prefix, channel) (":bitchat " + prefix + " PART " + channel + "\r\n")
#define RPL_PARTREASON(prefix, channel, reason) (":bitchat " + prefix + " PART " + channel + " " + reason + "\r\n")
#define RPL_PRIVMSG(prefix, target, message) (":bitchat " + prefix + " PRIVMSG " + target + " " + message + "\r\n")
#define RPL_TOPICCHANGED(prefix, channel, topic) (":bitchat " + prefix + " TOPIC " + channel + topic + "\r\n")
#define RPL_CHANGEMODE(prefix, channel, mode) (":bitchat " + prefix + " MODE " + channel + " " + mode + "\r\n") //TODO : not used

namespace reply {
	enum e_level { INFO, ERROR, DEBUG, REPLY };
	void log(e_level level, std::string message, std::string verbose);
	void log(e_level level, std::string message);
	void send(int fd, std::string reply);

} // namespace reply
#endif //REPLY_H