/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:49:32 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/10 10:33:19 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>

std::vector< std::string > VectorSplit(std::string &s,
									   const std::string &delimiter)
{
	std::vector< std::string > inputCli;
	size_t pos = 0;
	std::string token;

	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		inputCli.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	inputCli.push_back(s);

	return (inputCli);
}

Channel *createChannel(const std::string &channelName)
{
	//log(DEBUG, "-----createChannel-----");
	static Server &server = Server::GetInstanceServer(gPort, gPassword);

	std::map< std::string, Channel * >::iterator it =
		server.getAllCha().find(channelName);
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

bool handleJoin(std::string params, Client *currentCli)
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
			sendReply(currentCli->getFd(),
					  ERR_BADCHANNELKEY(currentCli->getNick(),
										curChan->getName()));
			return (false);
		}
	curChan->addClientChannel(curChan, currentCli);
	return (false);
}
