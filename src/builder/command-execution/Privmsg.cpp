/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:52:37 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/07 14:11:35 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>

//TODO need to add reply when client not a channel
//TODO need to add reply when channel not found
//only works for channel usage
bool handlePrivsmg(std::string params, Client *curCli)
{
	static Server &server = Server::GetServerInstance(gPort, gPassword);

	std::istringstream iss(params);
	std::string channelName;
	std::string message;

	iss >> channelName;
	std::getline(iss, message);

	//check if channel exist
	channelMapIt curChan =
		server.getAllCha().find(channelName);
	if (curChan->second == NULL) {
		log(DEBUG, "did not found channel");
		return (false);
	}

	//check if client is a channel
	std::map< int, Client * >::iterator senderIt =
		curChan->second->getCliInChan().find(curCli->getFd());
	if (senderIt == curChan->second->getCliInChan().end())
		return (false);

	//send message to everyone but the sender itself
	for (std::map< int, Client * >::iterator itCli =
			 curChan->second->getCliInChan().begin();
		 itCli != curChan->second->getCliInChan().end(); ++itCli) {
		if (itCli->first != curCli->getFd())
			sendReply(itCli->second->getFd(),
					  RPL_PRIVMSG(curCli->getPrefix(),
								  curChan->second->getName(), message));
	}
	return (true);
}