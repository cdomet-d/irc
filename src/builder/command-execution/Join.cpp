/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:49:32 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/19 16:42:37 by aljulien         ###   ########.fr       */
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
	server.addChan(newChan);
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
	logLevel(DEBUG, "-----handleJoin-----");
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
