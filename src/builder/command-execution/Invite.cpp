/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:03:32 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/19 16:13:44 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "Server.hpp"

void handleInvite(CmdSpec &cmd)
{
	static Server &server = Server::GetServerInstance(0, "");
	Channel &curChan = findCurChan(cmd[channel][0]);
	Client *sender = &cmd.getSender();

	Client *targetCli = NULL;
	for (clientMapIt itTarget = server.getAllCli().begin();
		 itTarget != server.getAllCli().end(); ++itTarget) {
		if (itTarget->second->cliInfo.getNick() == cmd[target][0]) {
			targetCli = itTarget->second;
		}
	}

	sendReply(sender->getFd(),
			  RPL_INVITING(targetCli->cliInfo.getNick(), cmd[channel][0]));
	sendReply(targetCli->getFd(),
			  RPL_INVITE(sender->cliInfo.getNick(),
						 targetCli->cliInfo.getNick(), cmd[channel][0]));
	curChan.addCli(INVITECLI, targetCli);
}
