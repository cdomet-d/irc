/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:52:14 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/18 17:00:26 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "Server.hpp"

void kickFromAllMap(Client *target, Channel *curChan)
{
	int fdTarget = target->getFd();

	curChan->getCliInChan().erase(fdTarget);
	clientMapIt itTarget;
	itTarget = curChan->getOpCli().find(fdTarget);
	if (itTarget != curChan->getOpCli().end())
		curChan->getOpCli().erase(fdTarget);
	itTarget = curChan->getInvitCli().find(fdTarget);
	if (itTarget != curChan->getInvitCli().end())
		curChan->getInvitCli().erase(fdTarget);
}

void handleKick(CmdSpec &cmd)
{
	Channel *curChan = findCurChan(cmd[channel][0]);
	Client *sender = &cmd.getSender();
	Client *target_ = NULL;

	for (size_t nbTarget = 0; nbTarget < cmd[target].getSize(); nbTarget++) {
		for (clientMapIt targetIt = curChan->getCliInChan().begin();
			 targetIt != curChan->getCliInChan().end(); ++targetIt) {
			if (targetIt->second->cliInfo.getNick() == cmd[target][nbTarget]) {
				target_ = targetIt->second;
				break;
			}
		}
		if (cmd[message].getSize())
			sendMessageChannel(
				curChan->getCliInChan(),
				RPL_KICK(sender->cliInfo.getPrefix(), curChan->getName(),
						 target_->cliInfo.getNick(), cmd[message][nbTarget]));
		else
			sendMessageChannel(curChan->getCliInChan(),
							   RPL_KICK(sender->cliInfo.getPrefix(),
										curChan->getName(),
										target_->cliInfo.getNick(), ""));
		kickFromAllMap(target_, curChan);
	}
}