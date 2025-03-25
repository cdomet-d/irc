/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlotte <charlotte@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:20:57 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/25 13:45:32 by charlotte        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "Server.hpp"

void nick(CmdSpec &cmd) {
	Client &sender = cmd.getSender();
	if (sender.cliInfo.getRegistration() != 3) {
		sender.cliInfo.setRegistration(2);
		reply::send(sender.getFd(), ":Introducing new nick \"" + cmd[nickname_][0] + "\"\r\n");
	}
	else
		reply::send(sender.getFd(), ":" + sender.cliInfo.getNick() + " changed his nickname to " + cmd[nickname_][0] + "\r\n");
	sender.cliInfo.setNick(cmd[nickname_][0]);
}
//TODO: send message to clients from channels in which sender is to inform of nickname change