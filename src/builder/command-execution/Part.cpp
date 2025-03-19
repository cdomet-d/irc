/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:12:52 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/19 15:44:53 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "Server.hpp"

void handlePart(CmdSpec &cmd)
{
	Client *sender = &cmd.getSender();
	Channel &curChan = findCurChan(cmd[channel_][0]);

	if (!cmd[message_].getSize())
		sendMessageChannel(
			curChan.getCliInChan(),
			RPL_PARTNOREASON(sender->cliInfo.getPrefix(), curChan.getName()));
	else
		sendMessageChannel(curChan.getCliInChan(),
						   RPL_PARTREASON(sender->cliInfo.getPrefix(),
										  curChan.getName(), cmd[message_][0]));

	int targetFd = sender->getFd();

	curChan.getCliInChan().erase(targetFd);
	logLevel(DEBUG, "erase client from channel");

	if (curChan.getOpCli().find(targetFd) != curChan.getOpCli().end()) {
		curChan.getOpCli().erase(targetFd);
		logLevel(DEBUG, "erase client from op");
	}
}
