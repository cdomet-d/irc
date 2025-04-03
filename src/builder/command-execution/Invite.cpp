/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:03:32 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/03 15:59:30 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "Server.hpp"

void invite(CmdSpec &cmd) {
	static Server &server = Server::GetServerInstance(0, "");
	Client *sender = &cmd.getSender();

	if (cmd[target_].empty()) {
		for (channelMapIt chan = server.getAllChan().begin();
			 chan != server.getAllChan().end(); ++chan) {
			if (chan->second->getInvitCli().find(sender->getFd()) !=
				chan->second->getInvitCli().end())
				reply::send_(
					sender->getFd(),
					RPL_INVITELIST(sender->cliInfo.getNick(), chan->first));
		}
		reply::send_(sender->getFd(),
					 RPL_ENDOFINVITELIST(sender->cliInfo.getNick()));
		return;
	}

	Channel &curChan = findCurChan(cmd[channel_][0]);
	//use NickMap
	Client *targetCli = NULL;
	for (clientMapIt itTarget = cmd.server_.getAllCli().begin();
		 itTarget != cmd.server_.getAllCli().end(); ++itTarget) {
		if (itTarget->second->cliInfo.getNick() == cmd[target_][0]) {
			targetCli = itTarget->second;
		}
	}

	reply::send_(sender->getFd(),
				 RPL_INVITING(sender->cliInfo.getNick(),
							  targetCli->cliInfo.getNick(), cmd[channel_][0]));
	reply::send_(targetCli->getFd(),
				 RPL_INVITE(sender->cliInfo.getPrefix(),
							targetCli->cliInfo.getNick(), cmd[channel_][0]));

	curChan.addCli(INVITECLI, targetCli);
}
