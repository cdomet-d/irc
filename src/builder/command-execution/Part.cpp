/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:12:52 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/10 16:01:52 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>

//use the define for the map of client and channel
bool handlePart(std::string params, Client *currentCli) {
	
	static Server &server = Server::GetInstanceServer(gPort, gPassword);

	std::istringstream iss(params);
	std::string channelName;
	std::string reason;

	iss >> channelName;
	std::getline(iss, reason);

	//needMoreParams
	if (channelName.empty() == true) {
		sendReply(currentCli->getFd(), ERR_NEEDMOREPARAMS(currentCli->getNick(), "PART"));
		log(DEBUG, "PART", "ERR_NEEDMOREPARAMS");
		return (false);
	}

	//noSuchChannel
	std::map<std::string, Channel *>::iterator currentChannel = server.getAllCha().find(channelName);
	if (currentChannel== server.getAllCha().end()) {
		sendReply(currentCli->getFd(), ERR_NOSUCHCHANNEL(currentCli->getNick(), channelName));
		log(DEBUG, "PART", "ERR_NOSUCHCHANNEL");
		return (false);
	}

	//notOnChannel
	std::map< int, Client * >::iterator senderIt = currentChannel->second->getCliInChannel().find(currentCli->getFd());
	if (senderIt == currentChannel->second->getCliInChannel().end()) {
		sendReply(currentCli->getFd(), ERR_NOTONCHANNEL(currentCli->getNick(), channelName));
		log(DEBUG, "PART", "ERR_NOTONCHANNEL");
		return (false);
	}
	
	for (std::map< int, Client * >::iterator itCli =
			currentChannel->second->getCliInChannel().begin();
		itCli != currentChannel->second->getCliInChannel().end(); ++itCli) {
		if (reason.empty() == true)
			sendReply(itCli->second->getFd(), RPL_PARTNOREASON(currentCli->getPrefix(), channelName));
		else
			sendReply(itCli->second->getFd(), RPL_PARTREASON(currentCli->getPrefix(), channelName, reason));
	}

	currentChannel->second->getCliInChannel().erase(senderIt);
	return (true);
}