/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:49:32 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/23 13:27:31 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Server.hpp"
#include <sstream>

Channel &createChan(const std::string &chanName) {
	static Server &server = Server::GetServerInstance(0, "");

	try {
		Channel &curChan = server.findChan(chanName);
		return (curChan);
	} catch (std::exception &e) {
		Channel *newChan = new Channel(chanName);
		newChan->setName(chanName);
		newChan->setModes();
		server.addChan(*newChan);
		return (*newChan);
	}
}

void sendNickList(clientMap curMap, Channel &curChan, const Client &sender) {
	std::string list;
	for (clientMapIt it = curMap.begin(); it != curMap.end(); ++it) {
		std::string prefix = "";
		if (curChan.getOpCli().find(it->first) != curChan.getOpCli().end()) {
			prefix = "@";
		}
		if (!list.empty()) {
			list += " ";
		}
		list += prefix + it->second->cliInfo.getNick();
	}
	RPL::send_(sender.getFd(), RPL_NAMREPLY(sender.cliInfo.getNick(), "=",
											curChan.getName(), list));
	RPL::send_(sender.getFd(),
			   RPL_ENDOFNAMES(sender.cliInfo.getNick(), curChan.getName()));
}

void joinMess(Channel &curChan, Client &sender) {
	for (clientMapIt itCli = curChan.getCliInChan().begin();
		 itCli != curChan.getCliInChan().end(); ++itCli) {
		RPL::send_(itCli->second->getFd(),
				   RPL_JOIN(sender.cliInfo.getPrefix(), curChan.getName()));
	}
	if (curChan.getTopic().empty() == false)
		RPL::send_(sender.getFd(),
				   RPL_TOPIC(sender.cliInfo.getNick(), curChan.getName(),
							 curChan.getTopic()));
	if (curChan.getOpCli().find(sender.getFd()) != curChan.getOpCli().end()) {
		const std::string &servName = "irc.bitchat.net";
		RPL::send_(sender.getFd(), RPL_MODE(servName, curChan.getName(),
											curChan.getModes(), ""));
	}
	sendNickList(curChan.getCliInChan(), curChan, sender);
}

void join(CmdSpec &cmd) {
	Client &sender = cmd.getSender();
	if (cmd[channel_][0] == "0") {
		partAllChans(cmd, "");
		return;
	}

	for (size_t nbChan = 0; nbChan < cmd[channel_].size(); nbChan++) {
		Channel &curChan = createChan(cmd[channel_][nbChan]);
		curChan.addClientToChan(curChan, sender);
		joinMess(curChan, sender);
	}
	return;
}
