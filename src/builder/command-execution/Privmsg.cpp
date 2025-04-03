/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:52:37 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/03 13:23:15 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Server.hpp"

//TODO boucler sur toutes les targets
void privmsg(CmdSpec &cmd) {
	Client *sender = &cmd.getSender();

	for (size_t nbTarg = 0; nbTarg < cmd[target_].size(); nbTarg++)
	{
		if (cmd[target_][nbTarg].find("#") == cmd[target_][nbTarg].npos) {
			for (clientMapIt itTarget = cmd.server_.getAllCli().begin();
				 itTarget != cmd.server_.getAllCli().end(); ++itTarget) {
				if (itTarget->second->cliInfo.getNick() == cmd[target_][nbTarg]) {
					reply::send_(itTarget->first,
								 RPL_PRIVMSG(sender->cliInfo.getPrefix(),
											 itTarget->second->cliInfo.getNick(),
											 cmd[message_][0]));
				}
			}
			continue ;
		}
		
		Channel &curChan = findCurChan(cmd[target_][nbTarg]);
		
		for (clientMapIt itCli = curChan.getCliInChan().begin();
			 itCli != curChan.getCliInChan().end(); ++itCli) {
			if (itCli->first != sender->getFd())
				reply::send_(itCli->second->getFd(),
							 RPL_PRIVMSG(sender->cliInfo.getPrefix(),
										 curChan.getName(), cmd[message_][0]));
		}
	}
}