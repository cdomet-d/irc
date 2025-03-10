/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:55:57 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/10 10:03:51 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Server.hpp"
#include <sstream>

void checkTopic(Channel *curChan, Client *curCli) {
	if (curChan->getTopic().empty() == true) {
		sendReply(curCli->getFd(),
				  RPL_NOTOPIC(curCli->getNick(), curChan->getName()));
		return;
	}
	sendReply(curCli->getFd(), RPL_TOPIC(curCli->getNick(), curChan->getName(),
										 curChan->getTopic()));
	return;
}

void clearTopic(Channel *curChan, Client *curCli) {
	curChan->setTopic("");
	for (std::map< int, Client * >::iterator it =
			 curChan->getCliInChan().begin();
		 it != curChan->getCliInChan().end(); ++it) {
		sendReply(it->second->getFd(),
				  RPL_NOTOPIC(curCli->getNick(), curChan->getName()));
	}
}

void changeTopic(Channel *curChan, Client *curCli, std::string topic) {
	topic.erase(1, 0); //remove the ':'
	curChan->getTopic().clear();
	curChan->setTopic(topic);
	for (std::map< int, Client * >::iterator it =
			 curChan->getCliInChan().begin();
		 it != curChan->getCliInChan().end(); ++it) {
		sendReply(it->second->getFd(),
				  RPL_TOPICCHANGED(curCli->getPrefix(), curChan->getName(),
								   curChan->getTopic()));
	}
}

bool handleTopic(std::string params, Client *curCli) {
	static Server &server = Server::GetServerInstance(gPort, gPassword);

	std::istringstream iss(params);
	std::string channelName;
	std::string topic;
	iss >> channelName;
	std::getline(iss, topic);

	channelMapIt curChan = server.getAllCha().find(channelName);

	//does the channel exists
	if (curChan == server.getAllCha().end()) {
		sendReply(
			curCli->getFd(),
			ERR_NOSUCHCHANNEL(server.getAllCli()[curCli->getFd()]->getNick(),
							  channelName));
		return (false);
	}

	//is the client on the channel
	std::map< int, Client * >::iterator whatCli =
		curChan->second->getCliInChan().find(curCli->getFd());
	if (whatCli == curChan->second->getCliInChan().end()) {
		sendReply(
			curCli->getFd(),
			ERR_NOTONCHANNEL(server.getAllCli()[curCli->getFd()]->getNick(),
							 curChan->second->getName()));
		return (false);
	}

	//if no params (= topic is empty) after channelname, client only checks the topic
	if (topic.empty() == true) {
		checkTopic(curChan->second, curCli);
		return (true);
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
