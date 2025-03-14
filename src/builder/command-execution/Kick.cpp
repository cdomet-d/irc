/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:52:14 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/14 13:42:29 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>
#include "Reply.hpp"

//TODO faire une fonction qui retire un client de toutes les maps d'un channel
bool handleKick(std::string params, Client *curCli) {
	static Server &server = Server::GetServerInstance(0, "");
	
	std::istringstream iss(params);
	std::string command = "KICK";
	std::string target;
	std::string channel;
	std::string reason;

	iss >> channel;
	iss >> target;
	getline(iss, reason);
	
	if (target.empty() == true || channel.empty() == true) {
		sendReply(curCli->getFd(), ERR_NEEDMOREPARAMS(command));
		return (false);
	}

	//does channel exists
	channelMapIt curChan = server.getAllChan().find(channel);
	if (curChan == server.getAllChan().end()) {
		sendReply(curCli->getFd(),
				  ERR_NOSUCHCHANNEL(curCli->getNick(), target));
		return (false);
	}
	//does client exist
	//get the instance of the kicked client
	clientMapIt itTarget;
	for (itTarget = curChan->second->getCliInChan().begin();
		 itTarget != curChan->second->getCliInChan().end(); ++itTarget) {
		if (itTarget->second->getNick() == target) {
			break ;
		}
	} //target not on channel
	if (itTarget == curChan->second->getCliInChan().end()) {
		sendReply(curCli->getFd(), ERR_NOSUCHNICK(target));
		return (false);		
	}
	//is client sending the invite on the channel
	clientMapIt senderIt =
	curChan->second->getCliInChan().find(curCli->getFd());
	if (senderIt == curChan->second->getCliInChan().end()) {
		sendReply(curCli->getFd(),
				  ERR_NOTONCHANNEL(curCli->getNick(), channel));
		return (false);
	}
	//is client sending the invite an OP on the channel
	senderIt = curChan->second->getOpCli().find(curCli->getFd());
	if (senderIt == curChan->second->getOpCli().end()) {
		sendReply(curCli->getFd(),
				  ERR_CHANOPRIVSNEEDED(curCli->getNick(), channel));
		return (false);
	}

	int fdTarget = itTarget->second->getFd();
	sendMessageChannel(curChan->second->getCliInChan(), RPL_KICK(curCli->getPrefix(), channel, itTarget->second->getNick(), reason));
	curChan->second->getCliInChan().erase(fdTarget);
	itTarget = curChan->second->getOpCli().find(fdTarget);
	if (itTarget != curChan->second->getOpCli().end())
		curChan->second->getOpCli().erase(fdTarget);
	itTarget = curChan->second->getInvitCli().find(fdTarget);
	if (itTarget != curChan->second->getInvitCli().end())
		curChan->second->getInvitCli().erase(fdTarget);
	
	return (true);
}