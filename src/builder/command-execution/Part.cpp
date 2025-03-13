/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:12:52 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/13 15:57:07 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>

//use the define for the map of client and channel
bool handlePart(std::string params, Client *curCli)
{
	static Server &server = Server::GetServerInstance(gPort, gPassword);

	std::istringstream iss(params);
	std::string chanName;
	std::string reason;

	iss >> chanName;
	std::getline(iss, reason);

	//needMoreParams
	if (chanName.empty() == true) {
		sendReply(curCli->getFd(), ERR_NEEDMOREPARAMS(curCli->getNick()));
		log(DEBUG, "PART", "ERR_NEEDMOREPARAMS");
		return (false);
	}

	//noSuchChannel
	channelMapIt curChan = server.getAllChan().find(chanName);
	if (curChan == server.getAllChan().end()) {
		sendReply(curCli->getFd(),
				  ERR_NOSUCHCHANNEL(curCli->getNick(), chanName));
		log(DEBUG, "PART", "ERR_NOSUCHCHANNEL");
		return (false);
	}
	//notOnChannel
	clientMap::iterator senderIt =
		curChan->second->getCliInChan().find(curCli->getFd());
	if (senderIt == curChan->second->getCliInChan().end()) {
		sendReply(curCli->getFd(),
				  ERR_NOTONCHANNEL(curCli->getNick(), chanName));
		log(DEBUG, "PART", "ERR_NOTONCHANNEL");
		return (false);
	}

	if (reason.empty() == true)
		sendMessageChannel(curChan->second->getCliInChan(),
						   RPL_PARTNOREASON(curCli->getPrefix(), chanName));
	else
		sendMessageChannel(
			curChan->second->getCliInChan(),
			RPL_PARTREASON(curCli->getPrefix(), chanName, reason));

	int targetFd = curCli->getFd();

	curChan->second->getCliInChan().erase(targetFd);
	log(DEBUG, "erase client from channel");

	//is Client op on channel ?
	if (curChan->second->getOpCli().find(targetFd) !=
		curChan->second->getOpCli().end()) {
		curChan->second->getOpCli().erase(targetFd);
		log(DEBUG, "erase client from op");
	}
	return (true);
}