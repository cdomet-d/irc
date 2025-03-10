/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:49:32 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/10 16:16:44 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>

Channel *createChannel(const std::string &channelName)
{
	static Server &server = Server::GetServerInstance(gPort, gPassword);

	channelMapIt it = server.getAllCha().find(channelName);
	if (it != server.getAllCha().end()) {
		return (it->second);
	}

	Channel *newChannel = new Channel(channelName);
	newChannel->setName(channelName);
	server.getAllCha().insert(
		std::pair< std::string, Channel * >(newChannel->getName(), newChannel));
	log(INFO, "Channel created: ", channelName);
	return (newChannel);
}

bool handleJoin(std::string params, Client *curCli)
{
	log(DEBUG, "-----handleJoin-----");

	std::istringstream iss(params);
	std::string channelName;
	std::string password;

	iss >> channelName;
	getline(iss, password);
	log(DEBUG, "channel name = ", channelName);

	Channel *curChan = createChannel(channelName);
	if (curChan->getIsPassword() == true)
		if (curChan->getPassword() != password) {
			sendReply(curCli->getFd(),
					  ERR_BADCHANNELKEY(curCli->getNick(), curChan->getName()));
			return (false);
		}
	curChan->addClientChannel(curChan, curCli);
	return (true);
}
