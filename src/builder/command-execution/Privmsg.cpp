/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:52:37 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/17 14:26:19 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>

bool handlePrivsmg(std::string params, Client *curCli)
{
	log(DEBUG, "HANDLEPRIVMSG");
	static Server &server = Server::GetServerInstance(0, "");

	std::istringstream iss(params);
	std::string target;
	std::string message;

	iss >> target;
	std::getline(iss, message);

	if (target.find("#") == target.npos) {
		for (clientMapIt itTarget = server.getAllCli().begin();
			 itTarget != server.getAllCli().end(); ++itTarget) {
			if (itTarget->second->getNick() == target) {
				sendReply(itTarget->first,
						  RPL_PRIVMSG(curCli->getPrefix(), target, message));
				return (true);
			}
		}
		sendReply(curCli->getFd(), ERR_NOSUCHNICK(target));
		return (false);
	}

	channelMapIt curChan = server.getAllChan().find(target);
	if (curChan == server.getAllChan().end()) {
		sendReply(curCli->getFd(),
				  ERR_NOSUCHCHANNEL(curCli->getNick(), target));
		return (false);
	}

	//check if client is a channel
	clientMapIt senderIt =
		curChan->second->getCliInChan().find(curCli->getFd());
	if (senderIt == curChan->second->getCliInChan().end()) {
		sendReply(curCli->getFd(), ERR_CANNOTSENDTOCHAN(curChan->second->getName()));	
		return (false);
	}
	Client *sender = senderIt->second;

	for (clientMapIt itCli = curChan->second->getCliInChan().begin();
		 itCli != curChan->second->getCliInChan().end(); ++itCli) {
		if (itCli->first != curCli->getFd())
			sendReply(itCli->second->getFd(),
					  RPL_PRIVMSG(curCli->cliInfo.getPrefix(),
								  curChan->second->getName(), message));
	}
	return (true);
}