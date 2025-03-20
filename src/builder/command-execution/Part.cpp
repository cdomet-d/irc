/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:12:52 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/20 10:55:01 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "Server.hpp"

void partExec(CmdSpec &cmd)
{
	static Server &server = Server::GetServerInstance(0, "");
	Client *sender = &cmd.getSender();
	Channel &curChan = findCurChan(cmd[channel][0]);

	if (!cmd[message].getSize())
		sendMessageChannel(
			curChan.getCliInChan(),
			RPL_PARTNOREASON(sender->cliInfo.getPrefix(), curChan.getName()));
	else
		sendMessageChannel(curChan.getCliInChan(),
						   RPL_PARTREASON(sender->cliInfo.getPrefix(),
										  curChan.getName(), cmd[message][0]));


	int targetFd = sender->getFd();
	curChan.removeCli(ALLCLI, targetFd);
	if (curChan.getOpCli().find(targetFd) != curChan.getOpCli().end())
		curChan.removeCli(OPCLI, targetFd);
	if (curChan.getCliInChan().empty() == true) {
		server.removeChan(&curChan);
		delete &curChan;
	}
}
