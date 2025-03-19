/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:49:32 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/19 14:19:06 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdSpec.hpp"
#include "Server.hpp"
#include <sstream>

Channel *createChan(const std::string &chanName)
{
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
	return (newChan);
}

/* void partAllChans(Client *curCli)
{
	for (stringVec::iterator currChanName = curCli->getJoinedChans().begin();
		 currChanName != curCli->getJoinedChans().end(); ++currChanName) {
		handlePart(*currChanName, curCli);
	}
	curCli->getJoinedChans().clear();
} */

void handleJoin(CmdSpec &cmd)
{
	Client *sender = &cmd.getSender();
	if (cmd[channel][0] == "0") {
		//partAllChans(sender);
		return;
	}

	for (size_t nbChan = 0; nbChan < cmd[channel].getSize(); nbChan++) {
		Channel *curChan = createChan(cmd[channel][nbChan]);
		curChan->addClientToChan(curChan, sender);
	}
	return;
}
