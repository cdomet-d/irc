/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:49:32 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/17 17:31:23 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdSpec.hpp"
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
	// log(INFO, "Channel created: ", chanName);
	return (newChan);
}

void partAllChans(Client *curCli)
{

	for (stringVec::iterator currChanName = curCli->getJoinedChans().begin();
		 currChanName != curCli->getJoinedChans().end(); ++currChanName) {
		handlePart(*currChanName, curCli);
	}
	curCli->getJoinedChans().clear();
}

//TODO :add invite only mode if mode +i is enable
//TODO :add check of password if mode  +k is enable
void handleJoin(CmdSpec &cmd)
{
 	log(DEBUG, "-----handleJoin-----");
	Client *sender = &cmd.getSender();
	if (cmd[channel][0] == "0") {
		partAllChans(sender);
		return ;
	}

	for (size_t nbChan = 0; nbChan < cmd[channel].getSize(); nbChan++) {
		Channel *curChan = createChan(cmd[channel][nbChan]);
		curChan->addClientToChan(curChan, sender);		
	}
	return ; 
}
