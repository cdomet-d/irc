/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:20:57 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/11 15:08:42 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "Server.hpp"

void nick(CmdSpec &cmd) {
	Client &sender = cmd.getSender();

	cmd.serv_.removeNickFromUsedNicks(sender.cliInfo.getNick());
	sender.cliInfo.setNick(cmd[nickname_][0]);
	cmd.serv_.addNickToUsedNicks(cmd[nickname_][0], sender.getFd());
	if (sender.cliInfo.getRegistration() == 3) {
		const stringVec &sdChans = sender.getJoinedChans();
		if (sdChans.empty())
			RPL::send_(cmd.getSdFd(),
					   RPL_NICK(sender.cliInfo.getPrefix(), cmd[nickname_][0]));
		for (size_t i = 0; i < sdChans.size(); i++) {
			Channel &curChan = findCurChan(sdChans[i]);
			sendMessageChannel(
				curChan.getCliInChan(),
				RPL_NICK(sender.cliInfo.getPrefix(), cmd[nickname_][0]));
		}
	}
	sender.cliInfo.setPrefix();
	if (sender.cliInfo.getRegistration() == 1) {
		sender.cliInfo.setRegistration(2);
		RPL::send_(cmd.getSdFd(), RPL_VALIDNICK(sender.cliInfo.getNick()));
	} else if (sender.cliInfo.getRegistration() == 2)
		registrationCompleted(sender);
}
