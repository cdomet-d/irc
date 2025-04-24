/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:49:32 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/24 14:55:45 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Exceptions.hpp"
#include "Server.hpp"
#include <sstream>

static void sendNickList(const clientMap &curMap, const Channel &curChan,
						 const Client &sender) {
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

static void joinMess(Channel &curChan, Client &sender) {
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
		Channel::partAllChans(cmd, "");
		return;
	}

	for (size_t nbChan = 0; nbChan < cmd[channel_].size(); nbChan++) {
		Channel &curChan = Channel::createChan(cmd[channel_][nbChan]);
		curChan.addClientToChan(curChan, sender);
		joinMess(curChan, sender);
	}
	return;
}
