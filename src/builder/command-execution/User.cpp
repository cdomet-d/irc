/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:48:49 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/27 14:20:13 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "Server.hpp"

void user(CmdSpec &cmd) {
	Client *sender = &cmd.getSender();
	sender->cliInfo.setUsername(cmd[username_][0]);
	sender->cliInfo.setRegistration(3);
	sender->cliInfo.setPrefix();
	reply::sendReply(cmd.getSender().getFd(),
					 RPL_USER(sender->cliInfo.getUsername()));
	reply::sendReply(sender->getFd(), REG_COMPLETE(sender->cliInfo.getNick()));
}
