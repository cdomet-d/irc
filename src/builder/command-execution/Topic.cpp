/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:55:57 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/06 13:57:41 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Server.hpp"
#include <sstream>

bool handleTopic(std::string params, int fd) {
	log(DEBUG, "-----handleTopic-----");

	static Server &server = Server::GetInstanceServer(gPort, gPassword);

	std::istringstream iss(params);
	std::string channelName;
	std::string topic;

	iss >> channelName;
	std::getline(iss, topic);

	std::map< std::string, Channel * >::iterator curChan =
		server.getAllCha().find(channelName);
	if (curChan == server.getAllCha().end()) {
		log(ERROR, "Channel not found: " + channelName);
		return (false);
	}
	log(DEBUG, "Channel found");

	//does the channel exists
	if (curChan->second == NULL) {
		sendReply(fd, ERR_NOSUCHCHANNEL(server.getAllCli()[fd]->getNick(),
										curChan->second->getName()));
		return (false);
	}

	clientMapIt whatCli =
		curChan->second->getCliInChannel().find(fd);
	//is the client on the channel
	if (whatCli == curChan->second->getCliInChannel().end()) {
		sendReply(fd, ERR_NOTONCHANNEL(whatCli->second->getNick(),
									   curChan->second->getName()));
		return (false);
	}
	log(DEBUG, "Client in channel found");

	//if no params (= topic is empty) after channelname, client only checks the topic
	if (topic.empty() == true) {
		if (curChan->second->getTopic().empty() == true) {
			log(DEBUG, "No topic found : ",
				RPL_NOTOPIC(whatCli->second->getNick(),
							curChan->second->getName()));
			sendReply(fd, RPL_NOTOPIC(whatCli->second->getNick(),
									  curChan->second->getName()));
			return (true);
		}
		log(DEBUG, "Topic found : ",
			RPL_TOPIC(whatCli->second->getNick(), curChan->second->getName(),
					  curChan->second->getTopic()));
		sendReply(fd, RPL_TOPIC(whatCli->second->getNick(),
								curChan->second->getName(),
								curChan->second->getTopic()));
		return (true);
	}

	//if topic is = ":", the client clears the topic for the channel
	//sends the notification to all clients of the channel
	if (topic == ":") {
		for (clientMapIt it =
				 curChan->second->getCliInChannel().begin();
			 it != curChan->second->getCliInChannel().end(); ++it) {
			log(DEBUG, "Topic cleared : ",
				RPL_TOPICCLEARED(whatCli->second->getPrefix(),
								 curChan->second->getName()));
			sendReply(it->second->getFd(),
					  RPL_TOPICCLEARED(whatCli->second->getPrefix(),
									   curChan->second->getName()));
		}
		return (true);
	}

	//if topic is :[other_topic], client changes the topic of the channel
	if (topic.empty() == false) {
		topic.erase(1, 0); //remove the ':'
		curChan->second->getTopic().clear();
		curChan->second->setTopic(topic);
		log(DEBUG, "Topic set : ",
			RPL_TOPICCHANGED(whatCli->second->getPrefix(),
							 curChan->second->getName(),
							 curChan->second->getTopic()));

		for (clientMapIt it =
				 curChan->second->getCliInChannel().begin();
			 it != curChan->second->getCliInChannel().end(); ++it) {
			sendReply(it->second->getFd(),
					  RPL_TOPICCHANGED(whatCli->second->getPrefix(),
									   curChan->second->getName(),
									   curChan->second->getTopic()));
		}
		return (true);
	}
	log(DEBUG, "command Topic failed unexpectedly");
	return (false);
}
