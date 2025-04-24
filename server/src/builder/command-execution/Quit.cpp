/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 08:57:57 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/24 09:44:31 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "Server.hpp"
#include <sstream>

void quit(CmdSpec &cmd) {
	Client *sender = &cmd.getSender();
	std::string message;
	if (!cmd[message_].empty())
		message = cmd[message_][0];
	else
		message = "You quit the server, see you next time !";
	sender->mess.clearMess();
	Channel::partAllChans(cmd, message);
	RPL::send_(sender->getFd(),
			   RPL_QUIT(sender->cliInfo.getPrefix(), message));
	RPL::send_(sender->getFd(),
			   RPL_ERROR(sender->cliInfo.getHostname(), "Client Quit"));
	std::stringstream ss;
	ss << "Client [" << sender->getFd() << "] disconnected\r\n";
	RPL::log(RPL::INFO, ss.str());
	cmd.serv_.removeCli(sender);
	close(sender->getFd());
	delete sender;
}
