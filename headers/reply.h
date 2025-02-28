/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:33:33 by aljulien          #+#    #+#             */
/*   Updated: 2025/02/28 17:06:01 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLY_H
# define REPLY_H
# include <string>
# include <cstring>

#define JOINED(nickname, channel) (":" + nickname + " JOIN :" + channel + "\r\n")

#define RPL_PRIVMSG(prefix, target, message) (":" + prefix + " PRIVMSG " + target + " :" + message + "\r\n")
#define RPL_TOPIC(nickname, channel, topic) (": 332 " + nickname + " " + channel + " :" + topic + "\r\n")
#define RPL_NOTOPIC(nickname, channel) (": 331 " + nickname + " " + channel + " :No topic is set" + "\r\n")

void sendReply(int fd, std::string reply);

#endif //REPLY_H