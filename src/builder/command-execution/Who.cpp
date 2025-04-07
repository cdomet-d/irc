/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:08:17 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/07 18:37:50 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "Reply.hpp"
#include "Server.hpp"
#include <sstream>

std::string buildNickList(clientMap curMap, Client *sender, Channel &curChan) {
	std::string list;
	(void)sender;
	for (clientMapIt it = curMap.begin(); it != curMap.end(); it++) {
		// if (it->first == sender->getFd())
		// 	continue;
		std::string prefix = "";
		if (curChan.getOpCli().find(it->first) != curChan.getOpCli().end()) {
			prefix = "@";
		}
		if (!list.empty()) {
			list += " ";
		}
		list += prefix + it->second->cliInfo.getNick();
	}
	return (list);
}

void sendNickList(std::string &nickList, Client *sender, Channel &curChan) {

	reply::send_(sender->getFd(), RPL_NAMREPLY(sender->cliInfo.getNick(), "=",
											   curChan.getName(), nickList));
	reply::send_(sender->getFd(),
				 RPL_ENDOFNAMES(sender->cliInfo.getNick(), curChan.getName()));
}

void who(CmdSpec &cmd) {
	Client *sender = &cmd.getSender();
	Channel &curChan = findCurChan(cmd[channel_][0]);
	std::string nickList;

	if (!cmd[flag_].empty() && cmd[flag_][0] == "o")
		nickList = buildNickList(curChan.getOpCli(), sender, curChan);
	else
		nickList = buildNickList(curChan.getCliInChan(), sender, curChan);
	sendNickList(nickList, sender, curChan);
	//TODO: use numeric reply RPL_WHOREPLY and RPL_ENDOFWHO instead of RPL_NAMREPLY and RPL_ENDOFNAMES?
}