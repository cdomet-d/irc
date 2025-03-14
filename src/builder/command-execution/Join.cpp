/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:49:32 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/14 13:42:15 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>

Channel *createChan(const std::string &chanName)
{
	//log(DEBUG, "-----createChan-----");
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
	log(INFO, "Channel created: ", chanName);
	return (newChan);
}

void partAllChans(Client *curCli)
{

	for (stringVec::iterator currChanName = curCli->getChans().begin();
		 currChanName != curCli->getChans().end(); ++currChanName) {
		handlePart(*currChanName, curCli);
	}
	curCli->getChans().clear();
}

bool isCliInvited(Client *curCli, Channel *curChan)
{
	clientMapIt isOp = curChan->getInvitCli().find(curCli->getFd());
	if (isOp == curChan->getInvitCli().end())
		return (false);
	return (true);
}

//TODO :add invite only mode if mode +i is enable
//TODO :add check of password if mode  +k is enable
bool handleJoin(std::string params, Client *curCli)
{
	std::istringstream iss(params);
	std::string chanName;
	std::string password;

	iss >> chanName;
	getline(iss, password);

	if (chanName == "0") {
		partAllChans(curCli);
		return (true);
	}

	Channel *curChan = createChan(chanName);
	if (curChan->getIsPassMatch() == true)
		if (curChan->getPassword() != password) {
			sendReply(curCli->getFd(),
					  ERR_BADCHANNELKEY(curCli->getNick(), curChan->getName()));
			return (false);
		}
	if (curChan->getInviteOnly() == true)
		if (isCliInvited(curCli, curChan) == false) {
			sendReply(curCli->getFd(), ERR_INVITEONLYCHAN(curChan->getName()));
			return (false);
		}
	curChan->addClientToChan(curChan, curCli);
	return (false);
}
