/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:20:57 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/04 12:12:10 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "Server.hpp"

void nick(CmdSpec &cmd) {
	Client &sender = cmd.getSender();

	if (sender.cliInfo.getRegistration() != 3)
		sender.cliInfo.setRegistration(2);
	if (sender.cliInfo.getNick() == "")
		cmd.serv_.removeNickFromUsedNicks(sender.cliInfo.getNick());
	sender.cliInfo.setNick(cmd[nickname_][0]);
	sender.cliInfo.setPrefix();
	cmd.serv_.addNickToUsedNicks(cmd[nickname_][0], sender.getFd());
	reply::send_(cmd.getSender().getFd(), RPL_NICK(sender.cliInfo.getNick()));
}
