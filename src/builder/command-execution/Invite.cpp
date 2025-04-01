/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:03:32 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/01 08:29:27 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "Server.hpp"

void invite(CmdSpec &cmd) {
	if (cmd[target_].empty()) {
		//TODO: print invite list
		return ;
	}
	Channel &curChan = findCurChan(cmd[channel_][0]);
	Client *sender = &cmd.getSender();

	//use NickMap
	Client *targetCli = NULL;
	for (clientMapIt itTarget = cmd.server_.getAllCli().begin();
		 itTarget != cmd.server_.getAllCli().end(); ++itTarget) {
		if (itTarget->second->cliInfo.getNick() == cmd[target_][0]) {
			targetCli = itTarget->second;
		}
	}

	reply::send_(sender->getFd(), RPL_INVITING(sender->cliInfo.getNick(),
												   targetCli->cliInfo.getNick(),
												   cmd[channel_][0]));
	reply::send_(targetCli->getFd(),
					 RPL_INVITE(sender->cliInfo.getPrefix(),
								targetCli->cliInfo.getNick(),
								cmd[channel_][0]));

	curChan.addCli(INVITECLI, targetCli);
}
