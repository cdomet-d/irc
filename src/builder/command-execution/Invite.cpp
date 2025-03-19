/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/03/19 17:06:13 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "Server.hpp"

void handleInvite(CmdSpec &cmd)
{
	static Server &server = Server::GetServerInstance(0, "");
	Channel &curChan = findCurChan(cmd[channel_][0]);
	Client *sender = &cmd.getSender();

	Client *targetCli = NULL;
	for (clientMapIt itTarget = server.getAllCli().begin();
		 itTarget != server.getAllCli().end(); ++itTarget) {
		if (itTarget->second->cliInfo.getNick() == cmd[target_][0]) {
			targetCli = itTarget->second;
		}
	}

	reply::send(sender->getFd(),
			  RPL_INVITING(targetCli->cliInfo.getNick(), cmd[channel_][0]));
	reply::send(targetCli->getFd(),
			  RPL_INVITE(sender->cliInfo.getNick(),
						 targetCli->cliInfo.getNick(), cmd[channel_][0]));
	curChan.getInvitCli().insert(clientPair(targetCli->getFd(), targetCli));
}
