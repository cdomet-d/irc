/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:08:17 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/09 16:19:03 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "Reply.hpp"
#include "Server.hpp"
#include <sstream>

void who(CmdSpec &cmd) {
	Channel &curChan = findCurChan(cmd[channel_][0]);
	std::string nickList;

	if (!cmd[flag_].empty() && cmd[flag_][0] == "o") {
		for (clientMapIt it = curChan.getOpCli().begin();
			 it != curChan.getOpCli().end(); ++it) {
			reply::send_(cmd.getSdFd(),
						 RPL_WHOREPLY(it->second->cliInfo.getNick(), cmd[channel_][0],
									  it->second->cliInfo.getUsername(),
									  it->second->cliInfo.getHostname(), "@",
									  it->second->cliInfo.getRealName()));
		}
	} else {
		std::string flag;
		for (clientMapIt it = curChan.getCliInChan().begin();
			 it != curChan.getCliInChan().end(); ++it) {
			flag = "";
			if (curChan.getOpCli().find(it->second->getFd()) !=
				curChan.getOpCli().end())
				flag = "@";
			reply::send_(cmd.getSdFd(),
						 RPL_WHOREPLY(it->second->cliInfo.getNick(),
									  cmd[channel_][0],
									  it->second->cliInfo.getUsername(),
									  it->second->cliInfo.getHostname(), flag,
									  it->second->cliInfo.getRealName()));
		}
	}
	reply::send_(cmd.getSdFd(),
				 RPL_ENDOFWHO(cmd.getSdNick(), cmd[channel_][0]));
}
