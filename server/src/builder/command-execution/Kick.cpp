/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:52:14 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/24 17:26:14 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Exceptions.hpp"
#include "Reply.hpp"
#include "Server.hpp"

static void kickFromAllMap(Client &target, Channel &curChan) {
	int fdTarget = target.getFd();

	curChan.removeCli(ALLCLI, fdTarget);
	curChan.removeCli(OPCLI, fdTarget);
	curChan.removeCli(INVITECLI, fdTarget);
	target.removeOneChan(curChan.getName());
}

void kick(CmdSpec &cmd) {
	Client &sender = cmd.getSender();
	try {
		Channel &curChan = cmd.serv_.findChan(cmd[channel_][0]);

		for (size_t nbTarget = 0; nbTarget < cmd[target_].size(); nbTarget++) {
			int fdTarget = cmd.serv_.getFdFromNick(cmd[target_][nbTarget]);
			Client &target = cmd.serv_.findCli(fdTarget);

			if (cmd[message_].size())
				RPL::sendMessageChannel(
					curChan.getCliInChan(),
					RPL_KICK(sender.cliInfo.getPrefix(), curChan.getName(),
							 target.cliInfo.getNick(), ":" + cmd[message_][0]));
			else
				RPL::sendMessageChannel(curChan.getCliInChan(),
										RPL_KICK(sender.cliInfo.getPrefix(),
												 curChan.getName(),
												 target.cliInfo.getNick(), ""));
			kickFromAllMap(target, curChan);
		}
		curChan.checkOnlyOperator(sender);
	} catch (ObjectNotFound &e) { RPL::log(RPL::ERROR, e.what()); }
}