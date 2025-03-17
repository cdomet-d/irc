/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:12:52 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/14 12:34:43 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Reply.hpp"
#include <sstream>

//use the define for the map of client and channel
bool handlePart(std::string params, Client *curCli) {
	
	static Server &server = Server::GetServerInstance(0, "");

	std::istringstream iss(params);
	std::string chanName;
	std::string reason;

	iss >> chanName;
	std::getline(iss, reason);

	//needMoreParams
	if (chanName.empty() == true) {
		sendReply(curCli->getFd(), ERR_NEEDMOREPARAMS(curCli->cliInfo.getNick(), "PART"));
		// log(DEBUG, "PART", "ERR_NEEDMOREPARAMS");
		return (false);
	}

	//noSuchChannel
	channelMapIt curChan = server.getAllChan().find(chanName);
	if (curChan== server.getAllChan().end()) {
		sendReply(curCli->getFd(), ERR_NOSUCHCHANNEL(curCli->cliInfo.getNick(), chanName));
		// log(DEBUG, "PART", "ERR_NOSUCHCHANNEL");
		return (false);
	}

	//notOnChannel
	clientMapIt senderIt = curChan->second->getCliInChan().find(curCli->getFd());
	if (senderIt == curChan->second->getCliInChan().end()) {
		sendReply(curCli->getFd(), ERR_NOTONCHANNEL(curCli->cliInfo.getNick(), chanName));
		// log(DEBUG, "PART", "ERR_NOTONCHANNEL");
		return (false);
	}
	
	for (clientMapIt itCli =
			curChan->second->getCliInChan().begin();
		itCli != curChan->second->getCliInChan().end(); ++itCli) {
		if (reason.empty() == true)
			sendReply(itCli->second->getFd(), RPL_PARTNOREASON(curCli->cliInfo.getPrefix(), chanName));
		else
			sendReply(itCli->second->getFd(), RPL_PARTREASON(curCli->cliInfo.getPrefix(), chanName, reason));
	}

	curChan->second->getCliInChan().erase(senderIt);
	return (true);
}