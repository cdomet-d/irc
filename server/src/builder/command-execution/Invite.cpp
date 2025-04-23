/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:03:32 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/23 12:46:44 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "Server.hpp"

void invite(CmdSpec &cmd) {
	Client &sender = cmd.getSender();

	if (cmd[target_].empty())
		return (cmd.serv_.checkChanInviteList(sender));

	try {
		Channel &curChan = cmd.serv_.findChan(cmd[channel_][0]);
		int fdTarget = cmd.serv_.getFdFromNick(cmd[target_][0]);
		Client &targetCli = cmd.serv_.findCli(fdTarget);

		RPL::send_(sender.getFd(),
				   RPL_INVITING(sender.cliInfo.getNick(),
								targetCli.cliInfo.getNick(), cmd[channel_][0]));
		RPL::send_(fdTarget,
				   RPL_INVITE(sender.cliInfo.getPrefix(),
							  targetCli.cliInfo.getNick(), cmd[channel_][0]));

		curChan.addCli(INVITECLI, targetCli);
	} catch (std::exception &e) { RPL::log(RPL::ERROR, e.what()); }
}
