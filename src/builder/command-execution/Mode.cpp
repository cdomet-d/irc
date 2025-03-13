/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:43:39 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/13 15:56:51 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>

/* void removeModes(Client * curCli, Channel *curChan, std::string modes) {
	for (size_t i = 0; modes.c_str()[i] != '+'; i++) {
		if (modes.c_str()[i] == 'i')
			curChan->setInviteOnly(true);
	//	if (modes.c_str()[i] == 'i')
	}
}

void addModes(Client * curCli, Channel *curChan, std::string modes) {
	
}

bool handleChannelMode(Client * curCli, std::string chanName, std::string modes) {
	static Server &server = Server::GetServerInstance(gPort, gPassword);
	
	//does the channel exist ?
	channelMapIt curChanIt = server.getAllChan().find(chanName);
	if (curChanIt == server.getAllChan().end()) {
		sendReply(curCli->getFd(),
				  ERR_NOSUCHCHANNEL(curCli->getNick(), chanName));
		log(DEBUG, "PART", "ERR_NOSUCHCHANNEL");
		return (false);
	}
	Channel *curChan = curChanIt->second;

	//returns the current mode of a channel : RPL_CHANNELMODEIS (324)
	if (modes == " ") {
		sendReply(curCli->getFd(), RPL_CHANNELMODEIS(curCli->getNick(), chanName));
		log(DEBUG, "Checking the mode: ",
			RPL_CHANNELMODEIS(curCli->getNick(), chanName));
		return (true);
	}

	//isCliOp ?
	clientMapIt senderIt =
		curChanIt->second->getOpCli().find(curCli->getFd());
	if (senderIt == curChanIt->second->getCliInChan().end()) {
		sendReply(curCli->getFd(),
				  ERR_CHANOPRIVSNEEDED(curCli->getNick(), chanName));
		log(DEBUG, "PART", "ERR_CHANOPRIVSNEEDED");
		return (false);
	}
	log(DEBUG, "Client is operator");

	for(size_t i = 0; i <  modes.size(); i++) {
		if (modes.c_str()[i] == '-') {
			modes.erase(i, 1);
			removeModes(curCli, curChan, modes);
		}
		if (modes.c_str()[i] == '+') {
			modes.erase(i, 1);
			addModes(curCli, curChan, modes);
		}
	}
	
	return (false);
	//change the modes
}

bool handleUserMode(Client *curCli, std::string userName, std::string modes) {
	(void)curCli;
	(void)userName;
	(void)modes;
	return (false);
}
*/
//the modes of a channel need to be empty if no moe is activated and +<modes> if any
bool handleMode(std::string params, Client *curCli)
{
	(void)curCli;
	log(DEBUG, "HandleMode");

	std::istringstream iss(params);
	std::string temp;

	iss >> temp;

	static Server &server = Server::GetServerInstance(gPort, gPassword);

	channelMapIt curChan = server.getAllChan().find("#test");

	curChan->second->setInviteOnly(true);
	//std::vector<std::string> modes;

	//iss >> chanName;
	//getline(iss, modes);
	//log(DEBUG, "chanName: ", chanName);
	//log(DEBUG, "modes: ", modes);

	//is the first param a chanel or a user ?
	//if (chanName.c_str()[0] == '#' || chanName.c_str()[1] == '#')
	//	handleChannelMode(curCli, chanName, modes);
	//else
	//	handleUserMode(curCli, chanName, modes);
	return (true);
}