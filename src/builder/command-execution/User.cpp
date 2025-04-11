/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:48:49 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/11 15:09:50 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "Server.hpp"

static std::string timeStamp() {
	char time_buf[80];
	time_t now = time(0);
	strftime(time_buf, sizeof(time_buf), "%d-%m-%Y %H:%M:%S", localtime(&now));
	return (time_buf);
}

void registrationCompleted(Client &sender) {
	sender.cliInfo.setRegistration(3);
	RPL::send_(sender.getFd(), RPL_WELCOME(sender.cliInfo.getNick(),
										   sender.cliInfo.getPrefix()));
	RPL::send_(sender.getFd(), RPL_YOURHOST(sender.cliInfo.getNick()));
	RPL::send_(sender.getFd(),
			   RPL_CREATED(sender.cliInfo.getNick(), timeStamp()));
	RPL::send_(sender.getFd(), RPL_MYINFO(sender.cliInfo.getNick()));
	RPL::send_(sender.getFd(), RPL_ISUPPORT(sender.cliInfo.getNick()));
	RPL::send_(sender.getFd(), RPL_MOTDSTART(sender.cliInfo.getNick()));
	RPL::send_(sender.getFd(), RPL_MOTD(sender.cliInfo.getNick()));
	RPL::send_(sender.getFd(), RPL_ENDOFMOTD(sender.cliInfo.getNick()));
}

void user(CmdSpec &cmd) {
	Client &sender = cmd.getSender();
	sender.cliInfo.setUsername(cmd[username_][0]);
	sender.cliInfo.setRealname(cmd[realname_][0]);
	sender.cliInfo.setPrefix();
	if (sender.cliInfo.getRegistration() == 1) {
		sender.cliInfo.setRegistration(2);
		RPL::send_(cmd.getSdFd(), RPL_USER(sender.cliInfo.getNick(),
										   sender.cliInfo.getUsername()));
	} else if (sender.cliInfo.getRegistration() == 2)
		registrationCompleted(sender);
}
