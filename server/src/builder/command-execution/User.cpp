/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:48:49 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/24 10:32:46 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "Server.hpp"
#include <ctime>

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
		sender.cliInfo.registrationCompleted(sender);
}
