/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:12:52 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/18 17:00:33 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "Server.hpp"

void handlePart(CmdSpec &cmd)
{
	Client *sender = &cmd.getSender();
	Channel *curChan = findCurChan(cmd[channel][0]);

	if (!cmd[message].getSize())
		sendMessageChannel(
			curChan->getCliInChan(),
			RPL_PARTNOREASON(sender->cliInfo.getPrefix(), curChan->getName()));
	else
		sendMessageChannel(curChan->getCliInChan(),
						   RPL_PARTREASON(sender->cliInfo.getPrefix(),
										  curChan->getName(), cmd[message][0]));

	int targetFd = sender->getFd();

	curChan->getCliInChan().erase(targetFd);
	logLevel(DEBUG, "erase client from channel");

	if (curChan->getOpCli().find(targetFd) != curChan->getOpCli().end()) {
		curChan->getOpCli().erase(targetFd);
		logLevel(DEBUG, "erase client from op");
	}
}
