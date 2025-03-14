/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:55:57 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/14 13:43:03 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Server.hpp"
#include <sstream>

void checkTopic(Channel *curChan, Client *curCli)
{
	if (curChan->getTopic().empty() == true) {
		sendReply(curCli->getFd(),
				  RPL_NOTOPIC(curCli->getNick(), curChan->getName()));
		return;
	}
	sendReply(curCli->getFd(), RPL_TOPIC(curCli->getNick(), curChan->getName(),
										 curChan->getTopic()));
	return;
}

void clearTopic(Channel *curChan, Client *curCli)
{
	curChan->setTopic("");
	//messageToAllChannel
	sendMessageChannel(curChan->getCliInChan(),
					   RPL_NOTOPIC(curCli->getNick(), curChan->getName()));
}

void changeTopic(Channel *curChan, Client *curCli, std::string topic)
{
	topic.erase(1, 0); //remove the ':'
	curChan->getTopic().clear();
	curChan->setTopic(topic);
	sendMessageChannel(curChan->getCliInChan(),
					   RPL_TOPICCHANGED(curCli->getPrefix(), curChan->getName(),
										curChan->getTopic()));
}

bool handleTopic(std::string params, Client *curCli)
{
	static Server &server = Server::GetServerInstance(0, "");

	std::istringstream iss(params);
	std::string chanName;
	std::string topic;
	iss >> chanName;
	std::getline(iss, topic);

	channelMapIt curChan = server.getAllChan().find(chanName);

	//does the channel exists
	if (curChan == server.getAllChan().end()) {
		sendReply(
			curCli->getFd(),
			ERR_NOSUCHCHANNEL(server.getAllCli()[curCli->getFd()]->getNick(),
							  chanName));
		return (false);
	}

	//is the client on the channel
	clientMapIt whatCli = curChan->second->getCliInChan().find(curCli->getFd());
	if (whatCli == curChan->second->getCliInChan().end()) {
		sendReply(
			curCli->getFd(),
			ERR_NOTONCHANNEL(server.getAllCli()[curCli->getFd()]->getNick(),
							 curChan->second->getName()));
		return (false);
	}

	//if no params (= topic is empty) after chanName, client only checks the topic
	if (topic.empty() == true) {
		checkTopic(curChan->second, curCli);
		return (true);
	}

	clientMapIt isOp = curChan->second->getOpCli().find(curCli->getFd());
	if (isOp == curChan->second->getOpCli().end() &&
		curChan->second->getTopicRestrict() == true) {
		sendReply(curCli->getFd(),
				  ERR_CHANOPRIVSNEEDED(curCli->getNick(),
									   curChan->second->getName()));
		return (false);
	}

	//if topic is = ":", the client clears the topic for the channel
	//sends the notification to all clients of the channel
	if (topic == " ::") {
		clearTopic(curChan->second, curCli);
		return (true);
	}

	//if topic is :[other_topic], client changes the topic of the channel
	if (topic.empty() == false) {
		changeTopic(curChan->second, curCli, topic);
		return (true);
	}

	return (false);
}
