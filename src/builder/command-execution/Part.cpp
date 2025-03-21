/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:12:52 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/21 10:48:37 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "CmdExecution.hpp"
#include "Server.hpp"

void partOneChan(Client *sender, Channel &curChan) {
    static Server &server = Server::GetServerInstance(0, "");

    int targetFd = sender->getFd();
    curChan.removeCli(ALLCLI, targetFd);
    if (curChan.getOpCli().find(targetFd) != curChan.getOpCli().end())
        curChan.removeCli(OPCLI, targetFd);
    if (curChan.getCliInChan().empty() == true) {
        server.removeChan(&curChan);
        delete &curChan;
    }
}

void part(CmdSpec &cmd)
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
    partOneChan(sender, curChan);
}
