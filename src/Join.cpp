/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:49:32 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/04 18:42:10 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include "Server.hpp"

std::string findChannelName(std::string &buffer)
{
	//log(DEBUG, "-----findChannelName-----");

	if (buffer.find("JOIN #") != buffer.npos)
		buffer.erase(buffer.find("JOIN #"), 6);
	return (buffer);
}

Channel *createChannel(const std::string& channelName)
{
	//log(DEBUG, "-----createChannel-----");
	static Server &server = Server::GetInstanceServer(gPort, gPassword);

	std::map<std::string, Channel*>::iterator it = server.getAllCha().find(channelName);
    if (it != server.getAllCha().end()) {
        return (it->second); }
    
	Channel* newChannel = new Channel(channelName);
	newChannel->setName(channelName);
	server.getAllCha().insert(std::pair< std::string, Channel * >(newChannel->getName(), newChannel));
	log(INFO, "Channel created: ", channelName);
	return (newChannel);
}

bool handleJoin(std::string params, int fd)
{
	log(DEBUG, "-----handleJoin-----");
	
	std::istringstream iss(params);
	std::string channelName;

	iss >> channelName;
	//remove the # of the channel name
	channelName.erase(0, 1);
	log(DEBUG, "channel name = ", channelName);

	Channel *currentChannel = createChannel(channelName);		
	currentChannel->addClientChannel(currentChannel, fd);
	return (false);
}