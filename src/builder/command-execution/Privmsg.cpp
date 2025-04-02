/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:52:37 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/02 13:55:37 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Server.hpp"

void privmsg(CmdSpec &cmd) {
	Client *sender = &cmd.getSender();

	if (cmd[target_][0].find("#") == cmd[target_][0].npos) {
		for (clientMapIt itTarget = cmd.server_.getAllCli().begin();
			 itTarget != cmd.server_.getAllCli().end(); ++itTarget) {
			if (itTarget->second->cliInfo.getNick() == cmd[target_][0]) {
				reply::send_(itTarget->first,
							 RPL_PRIVMSG(sender->cliInfo.getPrefix(),
										 itTarget->second->cliInfo.getNick(),
										 cmd[message_][0]));
				return;
			}
		}
	}
	Channel &curChan = findCurChan(cmd[target_][0]);

	for (clientMapIt itCli = curChan.getOpCli().begin();
		 itCli != curChan.getOpCli().end(); ++itCli) {
		std::cout << itCli->second->cliInfo.getNick() << std::endl;
	}

	if (cmd[target_][0].find("@") != cmd[target_][0].npos) {
		for (clientMapIt itCli = curChan.getOpCli().begin();
			 itCli != curChan.getOpCli().end(); ++itCli) {
			//	if (itCli->first != sender->getFd())
			reply::send_(itCli->second->getFd(),
						 RPL_PRIVMSG(sender->cliInfo.getPrefix(),
									 curChan.getName(), cmd[message_][0]));
		}
		return;
	}

	for (clientMapIt itCli = curChan.getCliInChan().begin();
		 itCli != curChan.getCliInChan().end(); ++itCli) {
		if (itCli->first != sender->getFd())
			reply::send_(itCli->second->getFd(),
						 RPL_PRIVMSG(sender->cliInfo.getPrefix(),
									 curChan.getName(), cmd[message_][0]));
	}
}