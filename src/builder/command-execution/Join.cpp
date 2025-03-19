/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:49:32 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/19 09:42:08 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>

Channel *createChan(const std::string &chanName)
{
	// log(DEBUG, "-----createChan-----");
	static Server &server = Server::GetServerInstance(0, "");

	channelMapIt it = server.getAllChan().find(chanName);
	if (it != server.getAllChan().end()) {
		return (it->second);
	}

	Channel *newChan = new Channel(chanName);
	newChan->setName(chanName);
	newChan->setModes();
	server.getAllChan().insert(
		std::pair< std::string, Channel * >(newChan->getName(), newChan));
	// reply::INFO, "Channel created: ", chanName);
	return (newChan);
}

bool handleJoin(std::string params, Client *curCli)
{
	// log(DEBUG, "-----handleJoin-----");

	std::istringstream iss(params);
	std::string chanName;
	std::string password;

	iss >> chanName;
	getline(iss, password);
	// log(DEBUG, "channel name = ", chanName);

	Channel *curChan = createChan(chanName);
	if (curChan->getIsPassMatch() == true)
		if (curChan->getPassword() != password) {
			reply::send(curCli->getFd(),
					  ERR_BADCHANNELKEY(curCli->cliInfo.getNick(), curChan->getName()));
			return (false);
		}
	curChan->addClientToChan(curChan, curCli);
	return (false);
}
