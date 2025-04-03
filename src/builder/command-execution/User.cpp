/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:48:49 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/03 18:59:33 by csweetin         ###   ########.fr       */
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
	sender.cliInfo.setPrefix();
	reply::send_(sender.getFd(), RPL_WELCOME(sender.cliInfo.getNick(),
											  sender.cliInfo.getPrefix()));
	reply::send_(sender.getFd(), RPL_YOURHOST(sender.cliInfo.getNick()));
	reply::send_(sender.getFd(),
				 RPL_CREATED(sender.cliInfo.getNick(), timeStamp()));
	reply::send_(sender.getFd(), RPL_MYINFO(sender.cliInfo.getNick()));
	reply::send_(sender.getFd(), RPL_ISUPPORT(sender.cliInfo.getNick()));
	reply::send_(sender.getFd(), REG_COMPLETE(sender.cliInfo.getNick()));
}

void user(CmdSpec &cmd) {
	Client &sender = cmd.getSender();
	sender.cliInfo.setUsername(cmd[username_][0]);
	if (sender.cliInfo.getRegistration() == 1) {
		sender.cliInfo.setRegistration(2);
		reply::send_(cmd.getSender().getFd(),
					RPL_USER(sender.cliInfo.getNick(), sender.cliInfo.getUsername()));
	}
	else if (sender.cliInfo.getRegistration() == 2)
		registrationCompleted(sender);
}
