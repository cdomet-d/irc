/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:52:37 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/19 12:46:43 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdSpec.hpp"
#include "Server.hpp"

void handlePrivsmg(CmdSpec &cmd)
{
	static Server &server = Server::GetServerInstance(0, "");
	Client *sender = &cmd.getSender();

	if (cmd[target][0].find("#") == cmd[target][0].npos) {
		for (clientMapIt itTarget = server.getAllCli().begin();
			 itTarget != server.getAllCli().end(); ++itTarget) {
			if (itTarget->second->cliInfo.getNick() == cmd[target][0]) {
				sendReply(itTarget->first,
						  RPL_PRIVMSG(sender->cliInfo.getPrefix(),
									  itTarget->second->cliInfo.getNick(),
									  cmd[message][0]));
				return;
			}
		}
	}
	Channel &curChan = findCurChan(cmd[target][0]);

	for (clientMapIt itCli = curChan.getCliInChan().begin();
		 itCli != curChan.getCliInChan().end(); ++itCli) {
		if (itCli->first != sender->getFd())
			sendReply(itCli->second->getFd(),
					  RPL_PRIVMSG(sender->cliInfo.getPrefix(),
								  curChan.getName(), cmd[message][0]));
	}
}