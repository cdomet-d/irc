/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:43:39 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/11 14:13:06 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>

bool handleMode(std::string params, Client *curCli)
{
	// log(DEBUG, "HandleMode");
	static Server &server = Server::GetServerInstance(gPort, gPassword);

	std::istringstream iss(params);
	std::string chanName;
	std::string modes;

	iss >> chanName;
	getline(iss, modes);
	// log(DEBUG, "chanName: ", chanName);
	// log(DEBUG, "modes: ", modes);

	channelMapIt curChan = server.getAllChan().find(chanName);
	if (curChan == server.getAllChan().end()) {
		sendReply(curCli->getFd(),
				  ERR_NOSUCHCHANNEL(curCli->getNick(), chanName));
		// log(DEBUG, "PART", "ERR_NOSUCHCHANNEL");
		return (false);
	}

	// log(DEBUG, "mode of channel:", curChan->second->getModes());
	// log(DEBUG, "channel exists");

	//returns the current mode of a channel : RPL_CHANNELMODEIS (324)
	if (modes.empty() == true) {
		sendReply(curCli->getFd(),
				  RPL_CHANNELMODEIS(curCli->getNick(), chanName,
									curChan->second->getModes()));
		// log(DEBUG, "Checking the mode: ",
			// RPL_CHANNELMODEIS(curCli->getNick(), chanName,
			// 				  curChan->second->getModes()));
		return (true);
	}
	// log(DEBUG, "wants to change the mode of the channel");

	//notOperator
	clientMapIt senderIt =
		curChan->second->getOpCli().find(curCli->getFd());
	if (senderIt == curChan->second->getCliInChan().end()) {
		sendReply(curCli->getFd(),
				  ERR_CHANOPRIVSNEEDED(curCli->getNick(), chanName));
		// log(DEBUG, "PART", "ERR_NOTONCHANNEL");
		return (false);
	}
	// log(DEBUG, "Client is opeator");
	return (true);
}