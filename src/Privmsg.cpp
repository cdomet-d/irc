/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:52:37 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/05 16:25:41 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>

//only works for channel usage
bool handlePrivsmg(std::string params, int fd)
{
	static Server &server = Server::GetInstanceServer(gPort, gPassword);

	std::istringstream iss(params);
	std::string channelName;
	std::string message;
	
	iss >> channelName;
	std::getline(iss, message);

	std::map< std::string, Channel * >::iterator currentChannel = server.getAllCha().find(channelName);
    if (currentChannel->second == NULL) {
		log(DEBUG, "did not found channel");
        return (false); }

    std::map<int, Client*>::iterator senderIt = currentChannel->second->getCliInChannel().find(fd);
    if (senderIt == currentChannel->second->getCliInChannel().end())
        return (false);
    Client* sender = senderIt->second;
    for (std::map<int, Client*>::iterator itCli = currentChannel->second->getCliInChannel().begin(); 
        itCli != currentChannel->second->getCliInChannel().end(); ++itCli) {
        if (itCli->first != fd)
            sendReply(itCli->second->getFd(), RPL_PRIVMSG(sender->getPrefix(), currentChannel->second->getName(), message));
	}
	return (true);

}