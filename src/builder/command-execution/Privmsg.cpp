/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:52:37 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/13 15:41:15 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>

bool handlePrivsmg(std::string params, Client *curCli)
{
	static Server &server = Server::GetServerInstance(gPort, gPassword);

	std::istringstream iss(params);
	std::string target;
	std::string message;

	iss >> target;
	std::getline(iss, message);

	if (target.find("#") == target.npos) {
		for (clientMapIt itTarget = server.getAllCli().begin(); itTarget != server.getAllCli().end(); ++itTarget) {
			if (itTarget->second->getNick() == target) {
				sendReply(itTarget->first, RPL_PRIVMSG(curCli->getPrefix(), target, message));
				return (true);
			}
		}
		sendReply(curCli->getFd(), ERR_NOSUCHNICK(target));
		return (false);
	}

	channelMapIt curChan = server.getAllChan().find(target);
	if (curChan == server.getAllChan().end()) {
		sendReply(curCli->getFd(), ERR_NOSUCHCHANNEL(curCli->getNick(), target));
		return (false);
	}

	//TODO : sendReply if client tries to send message to channel he's not a part of
	clientMapIt senderIt =
		curChan->second->getCliInChan().find(curCli->getFd());
	if (senderIt == curChan->second->getCliInChan().end())
		return (false);
	Client *sender = senderIt->second;

	for (clientMapIt itCli = curChan->second->getCliInChan().begin();
		 itCli != curChan->second->getCliInChan().end(); ++itCli) {
		if (itCli->first != curCli->getFd())
			sendReply(itCli->second->getFd(),
					  RPL_PRIVMSG(sender->getPrefix(),
								  curChan->second->getName(), message));
	}
	return (true);
}