/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:52:14 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/25 16:39:04 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "Server.hpp"
#include "CmdExecution.hpp"

void kickFromAllMap(Client *target, Channel &curChan)
{
	int fdTarget = target->getFd();

	curChan.removeCli(ALLCLI, fdTarget);
	clientMapIt itTarget;
	itTarget = curChan.getOpCli().find(fdTarget);
	if (itTarget != curChan.getOpCli().end())
		curChan.removeCli(OPCLI, fdTarget);
	itTarget = curChan.getInvitCli().find(fdTarget);
	if (itTarget != curChan.getInvitCli().end())
		curChan.removeCli(INVITECLI, fdTarget);
}

void kick(CmdSpec &cmd)
{
	Channel &curChan = findCurChan(cmd[channel_][0]);
	Client *sender = &cmd.getSender();
	Client *target = NULL;

	for (size_t nbTarget = 0; nbTarget < cmd[target_].size(); nbTarget++) {
		for (clientMapIt targetIt = curChan.getCliInChan().begin();
			 targetIt != curChan.getCliInChan().end(); ++targetIt) {
			if (targetIt->second->cliInfo.getNick() == cmd[target_][nbTarget]) {
				target = targetIt->second;
				break;
			}
		}
		if (cmd[message_].size())
			sendMessageChannel(
				curChan.getCliInChan(),
				RPL_KICK(sender->cliInfo.getPrefix(), curChan.getName(),
						 target->cliInfo.getNick(), cmd[message_][nbTarget]));
		else
			sendMessageChannel(curChan.getCliInChan(),
							   RPL_KICK(sender->cliInfo.getPrefix(),
										curChan.getName(),
										target->cliInfo.getNick(), ""));
		kickFromAllMap(target, curChan);
	}
}