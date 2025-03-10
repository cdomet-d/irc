/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:33:33 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/10 14:31:59 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLY_H
# define REPLY_H
# include <string>
# include <cstring>

//standard replies
#define RPL_TOPIC(nickname, channel, topic) (": 332 " + nickname + " " + channel + topic + "\r\n")
#define RPL_NOTOPIC(nickname, channel) (": 331 " + nickname + " " + channel + " :No topic is set" + "\r\n")
#define RPL_CHANNELMODEIS(nickname, channel, modes) (": 324 " + nickname + " " + channel + " :" + modes + "\r\n")
#define ERR_NICKNAMEINUSE(curNickname, nickname) (": 433 " + curNickname + " " + nickname + " :Nickname is already in use" + "\r\n")
#define ERR_NOSUCHCHANNEL(nickname, channel) (": 403 " + nickname + " " + channel + " :No such channel" + "\r\n")
#define ERR_NOTONCHANNEL(nickname, channel) (": 442 " + nickname + " " + channel + " :You're not on that channel" + "\r\n") 
#define ERR_CHANOPRIVSNEEDED(nickname, channel) (": 482 " + nickname + " " + channel + " :You're not channel operator" + "\r\n")
#define ERR_BADCHANNELKEY(nickname, channel) (" 475 " + nickname + " " + channel + " :Cannot join channel (+k)" + "\r\n")
#define ERR_NEEDMOREPARAMS(nickname, command) (": 461 " + nickname + " " + command + " :Not enough parameters" + "\r\n")
#define ERR_CHANOPRIVSNEEDED(nickname, channel) (": 482 " + nickname + " " + channel + " :You're not channel operator" + "\r\n")
#define ERR_UNKNOWNMODE(nichname, modechar) (": 472 " + nickname + " " + modechar + " :is unknown mode char to me" + "\r\n")

//user define replies
#define RPL_JOIN(nickname, channel) (":" + nickname + " JOIN :" + channel + "\r\n")
#define RPL_PRIVMSG(prefix, target, message) (":" + prefix + " PRIVMSG " + target + message + "\r\n")
#define RPL_TOPICCHANGED(prefix, channel, topic) (":" + prefix + " TOPIC " + channel + topic + "\r\n")
#define RPL_PARTREASON(prefix, channel, reason) (":" + prefix + " PART " + channel + " " + reason + "\r\n")
#define RPL_PARTNOREASON(prefix, channel) (":" + prefix + " PART " + channel + "\r\n")
#define RPL_CHANGEMODE(prefix, channel, mode) (":" + prefix + " MODE " + channel + " " + mode + "\r\n")

void sendReply(int fd, std::string reply);

#endif //REPLY_H
