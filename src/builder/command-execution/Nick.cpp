/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:20:57 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/27 14:16:04 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "Server.hpp"

void nick(CmdSpec &cmd) {
	Client *sender = &cmd.getSender();
	if (sender->cliInfo.getNick().empty() == true)
		sender->cliInfo.setRegistration(2);
	sender->cliInfo.setNick(cmd[nickname_][0]);
	sender->cliInfo.setPrefix();
	reply::sendReply(cmd.getSender().getFd(), RPL_NICK(sender->cliInfo.getNick()));
}
