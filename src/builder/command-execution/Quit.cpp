/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 08:57:57 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/10 17:22:50 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "Server.hpp"
#include <sstream>

void partAllChans(CmdSpec &cmd, const std::string &message) {
	Client *sender = &cmd.getSender();
	stringVec joinedChans = sender->getJoinedChans();

	for (size_t nbChan = 0; nbChan != joinedChans.size(); nbChan++) {
		Channel &curChan = findCurChan(joinedChans[nbChan]);
		if (cmd.getName() == "JOIN")
			partMess(sender, curChan, message);
		partOneChan(sender, curChan);
		if (cmd.getName() == "QUIT")
			sendMessageChannel(curChan.getCliInChan(),
							   RPL_QUIT(sender->cliInfo.getPrefix(), message));
		checkOnlyOperator(&curChan);
	}
}

void quit(CmdSpec &cmd) {
	Client *sender = &cmd.getSender();
	std::string message;
	if (!cmd[message_].empty())
		message = ":" + cmd[message_][0];

	sender->mess.clearMess();
	partAllChans(cmd, message);
	reply::send_(sender->getFd(),
				 RPL_QUIT(sender->cliInfo.getPrefix(), message));
	reply::send_(sender->getFd(), RPL_BYEYBE(sender->cliInfo.getNick()));
	std::stringstream ss;
	ss << "Client [" << sender->getFd() << "] disconnected\r\n";
	reply::log(reply::INFO, ss.str());
	cmd.serv_.removeCli(sender);
	close(sender->getFd());
	delete sender;
}
