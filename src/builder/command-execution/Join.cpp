/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:49:32 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/07 18:29:16 by csweetin         ###   ########.fr       */
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

void joinMess(Channel *curChan, Client *sender) {
	for (clientMapIt itCli = curChan->getCliInChan().begin();
		 itCli != curChan->getCliInChan().end(); ++itCli) {
		reply::send_(itCli->second->getFd(),
					 RPL_JOIN(sender->cliInfo.getPrefix(), curChan->getName()));
	}
	if (curChan->getTopic().empty() == false)
		reply::send_(sender->getFd(),
					 RPL_TOPIC(sender->cliInfo.getNick(), curChan->getName(),
							   curChan->getTopic()));
	if (curChan->getOpCli().find(sender->getFd()) != curChan->getOpCli().end()) {
		const std::string &servName = ":irc.bitchat.net";
		reply::send_(sender->getFd(),
					 RPL_MODE(servName, curChan->getName(),
							  curChan->getModes(), ""));
	}
	std::string nLst = buildNickList(curChan->getCliInChan(), sender, *curChan);
	sendNickList(nLst, sender, *curChan);
}

void join(CmdSpec &cmd) {
	Client *sender = &cmd.getSender();
	if (cmd[channel_][0] == "0") {
		partAllChans(cmd, "");
		return;
	}

	for (size_t nbChan = 0; nbChan < cmd[channel_].size(); nbChan++) {
		Channel *curChan = createChan(cmd[channel_][nbChan]);
		curChan->addClientToChan(curChan, sender);
		joinMess(curChan, sender);
	}
	return;
}
