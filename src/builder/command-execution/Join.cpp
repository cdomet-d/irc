/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:49:32 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/27 14:20:11 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Server.hpp"
#include <sstream>

Channel *createChan(const std::string &chanName) {
	static Server &server = Server::GetServerInstance(0, "");

	channelMapIt it = server.getAllChan().find(chanName);
	if (it != server.getAllChan().end())
		return (it->second);

	Channel *newChan = new Channel(chanName);
	newChan->setName(chanName);
	newChan->setModes();
	server.addChan(newChan);
	return (newChan);
}

void join(CmdSpec &cmd) {
	Client *sender = &cmd.getSender();
	if (cmd[channel_][0] == "0") {
		partAllChans(sender);
		return;
	}

	for (size_t nbChan = 0; nbChan < cmd[channel_].getSize(); nbChan++) {
		Channel *curChan = createChan(cmd[channel_][nbChan]);
		curChan->addClientToChan(curChan, sender);
	}
	return;
}
