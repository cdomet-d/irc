/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:03:32 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/11 15:08:28 by cdomet-d         ###   ########.fr       */
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
				RPL::send_(
					sender->getFd(),
					RPL_INVITELIST(sender->cliInfo.getNick(), chan->first));
		}
		RPL::send_(sender->getFd(),
				   RPL_ENDOFINVITELIST(sender->cliInfo.getNick()));
		return;
	}

	Channel &curChan = findCurChan(cmd[channel_][0]);
	int fdTarget = server.getUsedNick().find(cmd[target_][0])->second;
	Client *targetCli = server.getAllCli().find(fdTarget)->second;

	RPL::send_(sender->getFd(),
			   RPL_INVITING(sender->cliInfo.getNick(),
							targetCli->cliInfo.getNick(), cmd[channel_][0]));
	RPL::send_(fdTarget,
			   RPL_INVITE(sender->cliInfo.getPrefix(),
						  targetCli->cliInfo.getNick(), cmd[channel_][0]));

	curChan.addCli(INVITECLI, targetCli);
}
