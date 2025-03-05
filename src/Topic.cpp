/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:55:57 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/05 16:47:36 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include <sstream>

bool handleTopic(std::string params, int fd) {
	log(DEBUG, "-----handleTopic-----");
	
	static Server &server = Server::GetInstanceServer(gPort, gPassword);
	
	std::istringstream iss(params);
	std::string channelName;
	std::string topic;

	iss >> channelName;
	std::getline(iss, topic);

	std::map< std::string, Channel * >::iterator currentChannel = server.getAllCha().find(channelName);
	if (currentChannel == server.getAllCha().end()) {
		log(ERROR, "Channel not found: " + channelName);
		return (false);
	}
	log(DEBUG, "Channel found");

	//does the channel exists
	if (currentChannel->second == NULL) {
		sendReply(fd, ERR_NOSUCHCHANNEL(server.getAllCli()[fd]->getNick(), currentChannel->second->getName()));
		return (false); }

	std::map<int, Client*>::iterator whatCli = currentChannel->second->getCliInChannel().find(fd);
	//is the client on the channel
	if (whatCli == currentChannel->second->getCliInChannel().end()) {
		sendReply(fd, ERR_NOTONCHANNEL(whatCli->second->getNick(), currentChannel->second->getName()));
		return (false); }
	log(DEBUG, "Client in channel found");

	//if no params (= topic is empty) after channelname, client only checks the topic
	if (topic.empty() == true) {
		if (currentChannel->second->getTopic().empty() == true) {
			log(DEBUG, "No topic found : ", RPL_NOTOPIC(whatCli->second->getNick(), currentChannel->second->getName()));
			sendReply(fd, RPL_NOTOPIC(whatCli->second->getNick(), currentChannel->second->getName()));
			return (true);
		}
		log(DEBUG, "Topic found : ", RPL_TOPIC(whatCli->second->getNick(), currentChannel->second->getName(), currentChannel->second->getTopic()));
		sendReply(fd, RPL_TOPIC(whatCli->second->getNick(), currentChannel->second->getName(), currentChannel->second->getTopic()));
		return (true);
	}

	//if topic is = ":", the client clears the topic for the channel
	//sends the notification to all clients of the channel
	if (topic == ":") {
		for (std::map<int, Client *>::iterator it = currentChannel->second->getCliInChannel().begin();
			it != currentChannel->second->getCliInChannel().end(); ++it) {
				log(DEBUG, "Topic cleared : ", RPL_TOPICCLEARED(whatCli->second->getPrefix(), currentChannel->second->getName()));
				sendReply(it->second->getFd(), RPL_TOPICCLEARED(whatCli->second->getPrefix(), currentChannel->second->getName())); }
		return (true);
	}

	//if topic is :[other_topic], client changes the topic of the channel
	if (topic.empty() == false) {
		topic.erase(1, 0); //remove the ':'
		currentChannel->second->getTopic().clear();
		currentChannel->second->setTopic(topic);
		log(DEBUG, "Topic set : ", RPL_TOPICCHANGED(whatCli->second->getPrefix(), currentChannel->second->getName(), currentChannel->second->getTopic()));

		for (std::map<int, Client *>::iterator it = currentChannel->second->getCliInChannel().begin();
			it != currentChannel->second->getCliInChannel().end(); ++it) {
				sendReply(it->second->getFd(), RPL_TOPICCHANGED(whatCli->second->getPrefix(), currentChannel->second->getName(), currentChannel->second->getTopic())); }
		return (true);
	}
	log(DEBUG, "command Topic failed unexpectedly");
	return (false);
}
