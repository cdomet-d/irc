/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:12:52 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/01 17:10:40 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "Server.hpp"

void partOneChan(Client *sender, Channel &curChan) {
	int targetFd = sender->getFd();
	curChan.removeCli(ALLCLI, targetFd);
	if (curChan.getOpCli().find(targetFd) != curChan.getOpCli().end()) {
		curChan.removeCli(OPCLI, targetFd);
	}
}

void part(CmdSpec &cmd) {
	Client *sender = &cmd.getSender();
	Channel &curChan = findCurChan(cmd[channel_][0]);

	if (!cmd[message_].size())
		sendMessageChannel(
			curChan.getCliInChan(),
			RPL_PARTNOREASON(sender->cliInfo.getPrefix(), curChan.getName()));
	else {
		sendMessageChannel(curChan.getCliInChan(),
						   RPL_PARTREASON(sender->cliInfo.getPrefix(),
										  curChan.getName(), cmd[message_][0]));
	}
	partOneChan(sender, curChan);
	checkOnlyOperator(&curChan);
}
