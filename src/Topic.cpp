/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:55:57 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/06 11:58:20 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include <sstream>

void checkTopic(Channel *currentChannel, Client *whatCli, int fdClient) {
	if (currentChannel->getTopic().empty() == true) {
		log(DEBUG, "No topic found : ", RPL_NOTOPIC(whatCli->getNick(), currentChannel->getName()));
		sendReply(fdClient, RPL_NOTOPIC(whatCli->getNick(), currentChannel->getName()));
		return ;
	}
	log(DEBUG, "Topic found : ", RPL_TOPIC(whatCli->getNick(), currentChannel->getName(), currentChannel->getTopic()));
	sendReply(fdClient, RPL_TOPIC(whatCli->getNick(), currentChannel->getName(), currentChannel->getTopic()));
	return ;
}

void clearTopic(Channel *currentChannel, Client *whatCli) {
	log(DEBUG, "-----clearTopic-----");
	currentChannel->setTopic("");
	for (std::map<int, Client *>::iterator it = currentChannel->getCliInChannel().begin();
	it != currentChannel->getCliInChannel().end(); ++it) {
		sendReply(it->second->getFd(), RPL_NOTOPIC(whatCli->getNick(), currentChannel->getName()));
		log(DEBUG, "sending clear the topic lol");

	}
}

void changeTopic(Channel *currentChannel, Client *whatCli, std::string topic) {
	topic.erase(1, 0); //remove the ':'
	currentChannel->getTopic().clear();
	currentChannel->setTopic(topic);
	log(DEBUG, "Topic set : ", RPL_TOPICCHANGED(whatCli->getPrefix(), currentChannel->getName(), currentChannel->getTopic()));

	for (std::map<int, Client *>::iterator it = currentChannel->getCliInChannel().begin();
		it != currentChannel->getCliInChannel().end(); ++it) {
			sendReply(it->second->getFd(), RPL_TOPICCHANGED(whatCli->getPrefix(), currentChannel->getName(), currentChannel->getTopic())); }
}

bool handleTopic(std::string params, int fd) {
	log(DEBUG, "-----handleTopic-----");
	
	static Server &server = Server::GetInstanceServer(gPort, gPassword);
	
	std::istringstream iss(params);
	std::string channelName;
	std::string topic;	
	iss >> channelName;
	std::getline(iss, topic);

	std::map< std::string, Channel * >::iterator currentChannel = server.getAllCha().find(channelName);
	//does the channel exists
	if (currentChannel == server.getAllCha().end()) {
		sendReply(fd, ERR_NOSUCHCHANNEL(server.getAllCli()[fd]->getNick(), channelName));
		return (false); }

	std::map<int, Client*>::iterator whatCli = currentChannel->second->getCliInChannel().find(fd);
	//is the client on the channel
	if (whatCli == currentChannel->second->getCliInChannel().end()) {
		sendReply(fd, ERR_NOTONCHANNEL(server.getAllCli()[fd]->getNick(), currentChannel->second->getName()));
		return (false); }
	
	//if no params (= topic is empty) after channelname, client only checks the topic
	if (topic.empty() == true) {
		checkTopic(currentChannel->second, whatCli->second, fd);
		return (true); }

	//if topic is = ":", the client clears the topic for the channel
	//sends the notification to all clients of the channel
	if (topic == " ::") {
		clearTopic(currentChannel->second, whatCli->second);
		return (true); }
	
	//if topic is :[other_topic], client changes the topic of the channel
	if (topic.empty() == false) {
		changeTopic(currentChannel->second, whatCli->second, topic);
		return (true); }

	return (false);
}
