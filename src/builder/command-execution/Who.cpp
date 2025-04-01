/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:08:17 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/01 08:31:29 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "Reply.hpp"
#include "Server.hpp"
#include <sstream>

std::string buildNickList(clientMap curMap, Client *sender, Channel &curChan) {
	std::string list;

	for (clientMapIt it = curMap.begin(); it != curMap.end(); ++it) {
	   if (it->first == sender->getFd())
		   continue;
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

void who(CmdSpec &cmd) {
	(void)cmd;
	Client *sender = &cmd.getSender();
	Channel &curChan = findCurChan(cmd[channel_][0]);
	std::string nickList;

	//TODO : faire un try catch ou !empty ?
	//if (cmd[flag_][0] == "o") {
	//	nickList = buildNickList(curChan.getOpCli(), sender, curChan);
	//	return ;
	//}
	nickList = buildNickList(curChan.getCliInChan(), sender, curChan);		

	reply::send_(sender->getFd(),
			  RPL_NAMREPLY(sender->cliInfo.getNick(), "=", curChan.getName(), nickList));
	reply::send_(sender->getFd(),
			  RPL_ENDOFNAMES(sender->cliInfo.getNick(), curChan.getName()));

}