/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:33:33 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/12 10:31:25 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLY_H
# define REPLY_H
# include <string>
# include <cstring>

//standard replies

#define ERR_ALREADYREGISTRED()(":462 :You may not reregister\r\n")
// #define ERR_BADCHANNELKEY(channel) (":475 " + channel + " :Cannot join channel (+k)\r\n")
#define ERR_BADCHANNELKEY(nickname, channel) (" 475 " + nickname + " " + channel + " :Cannot join channel (+k)" + "\r\n")
#define ERR_BANNEDFROMCHAN(channel) (":474 " + channel + " :Cannot join channel (+b)\r\n")
#define ERR_CANNOTSENDTOCHAN(channel) (":404 " + channel + " :Cannot send to channel\r\n")
#define ERR_CHANNELISFULL(channel) (":471 " + channel + " :Cannot join channel (+l)\r\n")
// #define ERR_CHANOPRIVSNEEDED(channel) (":482 " + channel + " :You're not channel operator\r\n")
#define ERR_CHANOPRIVSNEEDED(nickname, channel) (": 482 " + nickname + " " + channel + " :You're not channel operator" + "\r\n")
#define ERR_ERRONEUSNICKNAME(nick) (":432 " + nick + " :Erroneous nickname\r\n")
#define ERR_INVITEONLYCHAN(channel) (":473 " + channel + " :Cannot join channel (+i)\r\n")
#define ERR_NEEDMOREPARAMS(command) (":461 " + command + " :Not enough parameters\r\n")
#define ERR_NICKNAMEINUSE(nick) (":433 " + nick + " :Nickname is already in use\r\n")
#define ERR_NONICKNAMEGIVEN()(":431 :No nickname given\r\n")
#define ERR_NORECIPIENT(command) (":411 :No recipient given (" + command + ")\r\n")
// #define ERR_NOSUCHCHANNEL(channel) (":403 " + channel + " :No such channel\r\n")
#define ERR_NOSUCHCHANNEL(nickname, channel) (": 403 " + nickname + " " + channel + " :No such channel" + "\r\n")
#define ERR_NOSUCHNICK(nickname) (":401 " + nickname + " :No such nick/channel\r\n")
#define ERR_NOTEXTTOSEND()(":412 :No text to send\r\n")
// #define ERR_NOTONCHANNEL(channel) (":442 " + channel + " :You're not on that channel\r\n")
#define ERR_NOTONCHANNEL(nickname, channel) (": 442 " + nickname + " " + channel + " :You're not on that channel" + "\r\n") 
#define ERR_TOOMANYCHANNELS(channel) (":405 " + channel + " :You have joined too many channels\r\n")
// #define ERR_UNKNOWNMODE(char) (":472 " + char + " :is unknown mode char to me\r\n")
#define ERR_UNKNOWNMODE(nickname, modechar) (": 472 " + nickname + " " + modechar + " :is unknown mode char to me" + "\r\n")
#define ERR_USERNOTINCHANNEL(nick, channel) (":441 " + nick + " " + channel + " :They aren't on that channel\r\n")
#define ERR_USERONCHANNEL(user, channel) (":443 " + user + " " + channel + " :is already on channel\r\n")
#define RPL_AWAY(nick, message) (":301 " + nick + " :" + message + "\r\n")
// #define RPL_CHANNELMODEIS(channel, mode, params) (":324 " + channel + " " + mode + " " + params + "\r\n")
#define RPL_CHANNELMODEIS(nickname, channel, modes) (": 324 " + nickname + " " + channel + " :" + modes + "\r\n")
#define RPL_CREATED(date) (":003 :This server was created " + date + "\r\n")
#define RPL_ENDOFNAMES(channel) (":366 " + channel + " :End of /NAMES list\r\n")
#define RPL_INVITING(channel, nick) (":341 " + channel + " " + nick + "\r\n")
#define RPL_MYINFO(servername, version, umodes, cmodes) (":004 " + servername + " " + version + " " + umodes + " " + cmodes + "\r\n")
#define RPL_NAMREPLY(symbol, channel, nicklist) (":353 " + symbol + " " + channel + " :" + nicklist + "\r\n")
// #define RPL_NOTOPIC(channel) (":331 " + channel + " :No topic is set\r\n")
#define RPL_NOTOPIC(nickname, channel) (": 331 " + nickname + " " + channel + " :No topic is set" + "\r\n")
// #define RPL_TOPIC(channel, topic) (":332 " + channel + " :" + topic + "\r\n")
#define RPL_TOPIC(nickname, channel, topic) (": 332 " + nickname + " " + channel + topic + "\r\n")
#define RPL_WELCOME(nick, user, host) (":001 " + nick + " :Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host + "\r\n")
#define RPL_YOURHOST(servername, version) (":002 :Your host is " + servername + ", running version " + version + "\r\n")

// Message parsing-related replies
#define ERR_TOOMANYTARGETS(nickname, target) (":407 " + nickname + " " + target + " :Too many targets\r\n")
#define ERR_INPUTTOOLONG(nickname) (":417 " + nickname + " :Input line was too long\r\n")
#define ERR_UNKNOWNCOMMAND(nickname, command) (":421 " + nickname + " " + command + " :Unknown command\r\n")

// Tokenization errors
// #define ERR_ERRONEUSNICKNAME(nickname, badnick) (":432 " + nickname + " " + badnick + " :Erroneous nickname\r\n")


//user define replies
#define RPL_JOIN(nickname, channel) (":" + nickname + " JOIN :" + channel + "\r\n")
#define RPL_PRIVMSG(prefix, target, message) (":" + prefix + " PRIVMSG " + target + message + "\r\n")
#define RPL_TOPICCHANGED(prefix, channel, topic) (":" + prefix + " TOPIC " + channel + topic + "\r\n")
#define RPL_PARTREASON(prefix, channel, reason) (":" + prefix + " PART " + channel + " " + reason + "\r\n")
#define RPL_PARTNOREASON(prefix, channel) (":" + prefix + " PART " + channel + "\r\n")
#define RPL_CHANGEMODE(prefix, channel, mode) (":" + prefix + " MODE " + channel + " " + mode + "\r\n")

void sendReply(int fd, std::string reply);

#endif //REPLY_H
