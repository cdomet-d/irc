/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:55:57 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/06 17:46:20 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Server.hpp"
#include <sstream>

void checkTopic(Channel *currentChannel, Client *currentCli)
{
	if (currentChannel->getTopic().empty() == true) {
		sendReply(currentCli->getFd(), RPL_NOTOPIC(currentCli->getNick(),
												   currentChannel->getName()));
		return;
	}
	sendReply(currentCli->getFd(),
			  RPL_TOPIC(currentCli->getNick(), currentChannel->getName(),
						currentChannel->getTopic()));
	return;
}

void clearTopic(Channel *currentChannel, Client *currentCli)
{
	currentChannel->setTopic("");
	for (std::map< int, Client * >::iterator it =
			 currentChannel->getCliInChannel().begin();
		 it != currentChannel->getCliInChannel().end(); ++it) {
		sendReply(it->second->getFd(), RPL_NOTOPIC(currentCli->getNick(),
												   currentChannel->getName()));
	}
}

void changeTopic(Channel *currentChannel, Client *currentCli, std::string topic)
{
	topic.erase(1, 0); //remove the ':'
	currentChannel->getTopic().clear();
	currentChannel->setTopic(topic);
	for (std::map< int, Client * >::iterator it =
			 currentChannel->getCliInChannel().begin();
		 it != currentChannel->getCliInChannel().end(); ++it) {
		sendReply(it->second->getFd(),
				  RPL_TOPICCHANGED(currentCli->getPrefix(),
								   currentChannel->getName(),
								   currentChannel->getTopic()));
	}
}

bool handleTopic(std::string params, Client *currentCli)
{
	static Server &server = Server::GetInstanceServer(gPort, gPassword);

	std::istringstream iss(params);
	std::string channelName;
	std::string topic;
	iss >> channelName;
	std::getline(iss, topic);

	std::map< std::string, Channel * >::iterator currentChannel =
		server.getAllCha().find(channelName);

	//does the channel exists
	if (currentChannel == server.getAllCha().end()) {
		sendReply(currentCli->getFd(),
				  ERR_NOSUCHCHANNEL(
					  server.getAllCli()[currentCli->getFd()]->getNick(),
					  channelName));
		return (false);
	}

	//is the client on the channel
	std::map< int, Client * >::iterator whatCli =
		currentChannel->second->getCliInChannel().find(currentCli->getFd());
	if (whatCli == currentChannel->second->getCliInChannel().end()) {
		sendReply(
			currentCli->getFd(),
			ERR_NOTONCHANNEL(server.getAllCli()[currentCli->getFd()]->getNick(),
							 currentChannel->second->getName()));
		return (false);
	}

	//if no params (= topic is empty) after channelname, client only checks the topic
	if (topic.empty() == true) {
		checkTopic(currentChannel->second, currentCli);
		return (true);
	}

	//if topic is = ":", the client clears the topic for the channel
	//sends the notification to all clients of the channel
	if (topic == " ::") {
		clearTopic(currentChannel->second, currentCli);
		return (true);
	}

	//if topic is :[other_topic], client changes the topic of the channel
	if (topic.empty() == false) {
		changeTopic(currentChannel->second, currentCli, topic);
		return (true);
	}

	return (false);
}
