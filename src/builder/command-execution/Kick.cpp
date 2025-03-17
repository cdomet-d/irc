/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:52:14 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/17 15:31:23 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Reply.hpp"
#include "Server.hpp"
#include <sstream>

void kickFromAllMap(Client *target, Channel *curChan) {
	int fdTarget = target->getFd();
	
	curChan->getCliInChan().erase(fdTarget);
	clientMapIt itTarget;
	itTarget = curChan->getOpCli().find(fdTarget);
	if (itTarget != curChan->getOpCli().end())
		curChan->getOpCli().erase(fdTarget);
	itTarget = curChan->getInvitCli().find(fdTarget);
	if (itTarget != curChan->getInvitCli().end())
		curChan->getInvitCli().erase(fdTarget);
}

bool handleKick(std::string params, Client *curCli)
{
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
				  ERR_NOSUCHCHANNEL(curCli->cliInfo.getNick(), target));
		return (false);
	}
	//does client exist
	//get the instance of the kicked client
	clientMapIt itTarget;
	for (itTarget = curChan->second->getCliInChan().begin();
		 itTarget != curChan->second->getCliInChan().end(); ++itTarget) {
		if (itTarget->second->cliInfo.getNick() == target) {
			break;
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
				  ERR_NOTONCHANNEL(curCli->cliInfo.getNick(), channel));
		return (false);
	}
	//is client sending the invite an OP on the channel
	senderIt = curChan->second->getOpCli().find(curCli->getFd());
	if (senderIt == curChan->second->getOpCli().end()) {
		sendReply(curCli->getFd(),
				  ERR_CHANOPRIVSNEEDED(curCli->cliInfo.getNick(), channel));
		return (false);
	}

	sendMessageChannel(curChan->second->getCliInChan(),
					   RPL_KICK(curCli->cliInfo.getPrefix(), channel,
								itTarget->second->cliInfo.getNick(), reason));
	kickFromAllMap(itTarget->second, curChan->second);

	return (true);
}