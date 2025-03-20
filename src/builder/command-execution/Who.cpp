/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:08:17 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/20 12:41:52 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Reply.hpp"
#include "Server.hpp"
#include <sstream>

bool whoExec(std::string params, Client *curCli)
{
	static Server &server = Server::GetServerInstance(0, "");

	std::istringstream iss(params);
	std::string channel;
	std::string command = "WHO";

	iss >> channel;

	//is there enough params
	if (channel.empty() == true) {
		reply::send(curCli->getFd(), ERR_NEEDMOREPARAMS(curCli->cliInfo.getNick(), command));
		return (false);
	}

	//does channel exists
	channelMapIt curChan = server.getAllChan().find(channel);
	if (curChan == server.getAllChan().end()) {
		reply::send(curCli->getFd(),
				  ERR_NOSUCHCHANNEL(curCli->cliInfo.getNick(), channel));
		return (false);
	}

	//is client sending the command on the channel
	clientMapIt senderIt =
		curChan->second->getCliInChan().find(curCli->getFd());
	if (senderIt == curChan->second->getCliInChan().end()) {
		reply::send(curCli->getFd(),
				  ERR_NOTONCHANNEL(curCli->cliInfo.getNick(), channel));
		return (false);
	}

	// Build the nickname list first
	std::string nickList;
	for (clientMapIt it = curChan->second->getCliInChan().begin();
		 it != curChan->second->getCliInChan().end(); ++it) {
		if (it->first == curCli->getFd())
			continue;
		std::string prefix = "";
		if (curChan->second->getOpCli().find(it->first) !=
			curChan->second->getOpCli().end()) {
			prefix = "@";
		}
		if (!nickList.empty()) {
			nickList += " ";
		}
		nickList += prefix + it->second->cliInfo.getNick();
	}

	// Send the full list
	reply::send(curCli->getFd(),
			  RPL_NAMREPLY(curCli->cliInfo.getNick(), "=", channel, nickList));
	reply::send(curCli->getFd(),
			  RPL_ENDOFNAMES(curCli->cliInfo.getNick(), channel));

	return (true);
}