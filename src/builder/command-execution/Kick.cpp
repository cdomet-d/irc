/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:52:14 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/19 16:34:03 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "Server.hpp"

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

void handleKick(CmdSpec &cmd)
{
	Channel &curChan = findCurChan(cmd[channel][0]);
	Client *sender = &cmd.getSender();
	Client *target_ = NULL;

	for (size_t nbTarget = 0; nbTarget < cmd[target].getSize(); nbTarget++) {
		for (clientMapIt targetIt = curChan.getCliInChan().begin();
			 targetIt != curChan.getCliInChan().end(); ++targetIt) {
			if (targetIt->second->cliInfo.getNick() == cmd[target][nbTarget]) {
				target_ = targetIt->second;
				break;
			}
		}
		if (cmd[message].getSize())
			sendMessageChannel(
				curChan.getCliInChan(),
				RPL_KICK(sender->cliInfo.getPrefix(), curChan.getName(),
						 target_->cliInfo.getNick(), cmd[message][nbTarget]));
		else
			sendMessageChannel(curChan.getCliInChan(),
							   RPL_KICK(sender->cliInfo.getPrefix(),
										curChan.getName(),
										target_->cliInfo.getNick(), ""));
		kickFromAllMap(target_, curChan);
	}
}