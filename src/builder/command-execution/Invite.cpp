/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:03:32 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/15 10:39:00 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "Server.hpp"

void invite(CmdSpec &cmd) {
	static Server &server = Server::GetServerInstance(0, "");
	Client *sender = &cmd.getSender();

	if (cmd[target_].empty())
		return (server.checkChanInviteList(sender));

	Channel &curChan = findCurChan(cmd[channel_][0]);
	int fdTarget = server.getFdFromNick(cmd[target_][0]);
	Client *targetCli = server.findCli(fdTarget);

	RPL::send_(sender->getFd(),
			   RPL_INVITING(sender->cliInfo.getNick(),
							targetCli->cliInfo.getNick(), cmd[channel_][0]));
	RPL::send_(fdTarget,
			   RPL_INVITE(sender->cliInfo.getPrefix(),
						  targetCli->cliInfo.getNick(), cmd[channel_][0]));

	curChan.addCli(INVITECLI, targetCli);
}
