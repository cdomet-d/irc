/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:55:57 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/19 16:57:55 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdSpec.hpp"
#include "Server.hpp"

void checkTopic(Channel &curChan, Client *curCli)
{
	if (curChan.getTopic().empty() == true) {
		reply::send(curCli->getFd(),
				  RPL_NOTOPIC(curCli->cliInfo.getNick(), curChan.getName()));
		return;
	}
	reply::send(curCli->getFd(),
			  RPL_TOPIC(curCli->cliInfo.getNick(), curChan.getName(),
						curChan.getTopic()));
	return;
}

void clearTopic(Channel &curChan, Client *curCli)
{
	curChan.setTopic("");
	sendMessageChannel(
		curChan.getCliInChan(),
		RPL_NOTOPIC(curCli->cliInfo.getNick(), curChan.getName()));
}

void changeTopic(Channel &curChan, Client *curCli, std::string topic)
{
	topic.erase(1, 0); //remove the ':'
	curChan.setTopic(topic);
	sendMessageChannel(curChan.getCliInChan(),
					   RPL_TOPICCHANGED(curCli->cliInfo.getPrefix(),
										curChan.getName(),
										curChan.getTopic()));
}

void handleTopic(CmdSpec &cmd)
{
	Client *sender = &cmd.getSender();
	Channel &curChan = findCurChan(cmd[channel_][0]);

	//if no params (= topic is empty) after chanName, client only checks the topic
	if (!cmd[topic_].getSize()) {
		checkTopic(curChan, sender);
		return;
	}
	//if topic is = ":", the client clears the topic for the channel
	//sends the notification to all clients of the channel
	if (cmd[topic_][0] == ":") {
		clearTopic(curChan, sender);
		return;
	}

	//if topic is :[other_topic], client changes the topic of the channel
	if (cmd[topic_][0].empty() == false) {
		changeTopic(curChan, sender, cmd[topic_][0]);
		return;
	}
}
