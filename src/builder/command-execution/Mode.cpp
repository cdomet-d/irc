/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:43:39 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/10 14:29:02 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>

bool handleMode(std::string params, Client *currentCli) {
	log(DEBUG, "HandleMode");
	static Server &server = Server::GetInstanceServer(gPort, gPassword);
	
	std::istringstream iss(params);
	std::string channelName;
	std::string modes;

	iss >> channelName;
	getline(iss, modes);
	log(DEBUG, "channelName: ", channelName);
	log(DEBUG, "modes: ", modes);

	std::map<std::string, Channel *>::iterator currentChannel = server.getAllCha().find(channelName);
	if (currentChannel== server.getAllCha().end()) {
		sendReply(currentCli->getFd(), ERR_NOSUCHCHANNEL(currentCli->getNick(), channelName));
		log(DEBUG, "PART", "ERR_NOSUCHCHANNEL");
		return (false);
	}

	log(DEBUG, "mode of channel:", currentChannel->second->getModes());
	log(DEBUG, "channel exists");

	//returns the current mode of a channel : RPL_CHANNELMODEIS (324)
	if (modes.empty() == true) {
		sendReply(currentCli->getFd(), RPL_CHANNELMODEIS(currentCli->getNick(), channelName, currentChannel->second->getModes()));
		log(DEBUG, "Checking the mode: ", RPL_CHANNELMODEIS(currentCli->getNick(), channelName, currentChannel->second->getModes()));
		return (true);
	}

	log(DEBUG, "wants to change the mode of the channel");
	
	//notOperator
	std::map< int, Client * >::iterator senderIt = currentChannel->second->getOpCli().find(currentCli->getFd());
	if (senderIt == currentChannel->second->getCliInChannel().end()) {
		sendReply(currentCli->getFd(), ERR_CHANOPRIVSNEEDED(currentCli->getNick(), channelName));
		log(DEBUG, "PART", "ERR_NOTONCHANNEL");
		return (false);
	}

	log(DEBUG, "Client is opeator");

	return (true);
}