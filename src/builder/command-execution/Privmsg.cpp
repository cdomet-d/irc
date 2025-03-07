/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:52:37 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/06 13:57:12 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>

//only works for channel usage
bool handlePrivsmg(std::string params, int fd) {
	static Server &server = Server::GetInstanceServer(gPort, gPassword);

	std::istringstream iss(params);
	std::string channelName;
	std::string message;

	iss >> channelName;
	std::getline(iss, message);

	std::map< std::string, Channel * >::iterator curChan =
		server.getAllCha().find(channelName);
	if (curChan->second == NULL) {
		log(DEBUG, "did not found channel");
		return (false);
	}

	clientMapIt senderIt =
		curChan->second->getCliInChannel().find(fd);
	if (senderIt == curChan->second->getCliInChannel().end())
		return (false);
	Client *sender = senderIt->second;
	for (clientMapIt itCli =
			 curChan->second->getCliInChannel().begin();
		 itCli != curChan->second->getCliInChannel().end(); ++itCli) {
		if (itCli->first != fd)
			sendReply(itCli->second->getFd(),
					  RPL_PRIVMSG(sender->getPrefix(),
								  curChan->second->getName(), message));
	}
	return (true);
}