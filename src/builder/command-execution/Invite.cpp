/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:03:32 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/13 14:40:26 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "reply.h"
#include<sstream>

bool handleInvite(std::string params, Client *curCli) {

	log(DEBUG, "----handleInvite----");
	static Server &server = Server::GetServerInstance(gPort, gPassword);

	std::istringstream iss(params);
	std::string target;
	std::string channel;

	iss >> target;
	iss >> channel;

	//is there enough params
	if (target.empty() == true || channel.empty() == true) {
		sendReply(curCli->getFd(), ERR_NEEDMOREPARAMS(curCli->getNick(), "INVITE"));
		return (false);
	}
	//does channel exists
	channelMapIt curChan = server.getAllChan().find(channel);
	if (curChan == server.getAllChan().end()) {
		sendReply(curCli->getFd(), ERR_NOSUCHCHANNEL(curCli->getNick(), target));
		return (false);
	}
	//does client exist
	//get the instance of the invited client
	Client *targetCli = NULL;
	for (clientMapIt itTarget = server.getAllCli().begin(); itTarget != server.getAllCli().end(); ++itTarget) {
		if (itTarget->second->getNick() == target) {
			targetCli = itTarget->second;
		}
	}
	//the message ends-up on the main page of IRC
	if (targetCli == NULL) {
		sendReply(curCli->getFd(), ERR_NOSUCHNICK(curCli->getNick(), target));
		return (false);
	}
	//is client sending the invite on the channel
    clientMapIt senderIt = curChan->second->getCliInChan().find(curCli->getFd());
    if (senderIt == curChan->second->getCliInChan().end()) {
        sendReply(curCli->getFd(), ERR_NOTONCHANNEL(curCli->getNick(), channel));
        return (false);
    }
	//is client sending the invite an OP on the channel 
	senderIt = curChan->second->getOpCli().find(curCli->getFd());
	if (senderIt == curChan->second->getOpCli().end()) {
        sendReply(curCli->getFd(), ERR_CHANOPRIVSNEEDED(curCli->getNick(), channel));
        return (false);
    }

	//is the invited client already on the channel
	//the message ends-up on the main page of IRC
	clientMapIt itTarget = curChan->second->getCliInChan().find(targetCli->getFd());
	if (itTarget != curChan->second->getCliInChan().end()) {
		sendReply(curCli->getFd(), ERR_USERONCHANNEL(curCli->getNick(), targetCli->getNick(), channel));
		return (false);
	} 

	//sendInvite to invited client and sending client
	sendReply(curCli->getFd(), RPL_INVITING(curCli->getNick(), targetCli->getNick(), channel));
	sendReply(targetCli->getFd(), RPL_INVITE(curCli->getNick(), targetCli->getNick(), channel));
	curChan->second->getInvitCli().insert(clientPair(targetCli->getFd(), targetCli));

	return (true);
}
