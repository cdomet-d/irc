/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:52:37 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/06 17:46:11 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>

//TODO need to add reply when client not a channel
//TODO need to add reply when channel not found
//only works for channel usage
bool handlePrivsmg(std::string params, Client *currentCLi)
{
	static Server &server = Server::GetInstanceServer(gPort, gPassword);

	std::istringstream iss(params);
	std::string channelName;
	std::string message;

	iss >> channelName;
	std::getline(iss, message);

	//check if channel exist
	std::map< std::string, Channel * >::iterator currentChannel =
		server.getAllCha().find(channelName);
	if (currentChannel->second == NULL) {
		log(DEBUG, "did not found channel");
		return (false);
	}

	//check if client is a channel
	std::map< int, Client * >::iterator senderIt =
		currentChannel->second->getCliInChannel().find(currentCLi->getFd());
	if (senderIt == currentChannel->second->getCliInChannel().end())
		return (false);

	//send message to everyone but the sender itself
	for (std::map< int, Client * >::iterator itCli =
			 currentChannel->second->getCliInChannel().begin();
		 itCli != currentChannel->second->getCliInChannel().end(); ++itCli) {
		if (itCli->first != currentCLi->getFd())
			sendReply(itCli->second->getFd(),
					  RPL_PRIVMSG(currentCLi->getPrefix(),
								  currentChannel->second->getName(), message));
	}
	return (true);
}