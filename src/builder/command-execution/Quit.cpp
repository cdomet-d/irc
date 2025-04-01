/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 08:57:57 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/01 08:13:36 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "Server.hpp"
#include <sstream>

void partAllChans(Client *sender) {
	for (stringVecItConst currChanName = sender->getJoinedChans().begin();
		 currChanName != sender->getJoinedChans().end(); ++currChanName) {
		std::string tempMess = "PART " + *currChanName + "\n\r";
		sender->mess.setMess(tempMess);
		buffer_manip::prepareCommand(*sender);
		sender->removeOneChan(*currChanName);
	}
}

void quit(CmdSpec &cmd) {
	static Server &server = Server::GetServerInstance(0, "");

	Client *sender = &cmd.getSender();
	sender->mess.clearMess();
	partAllChans(sender);
	reply::send_(sender->getFd(), RPL_BYEYBE(sender->cliInfo.getNick()));
	std::stringstream ss;
	ss << "Client [" << sender->getFd() << "] deconnected";
	reply::log(reply::INFO, ss.str());
	server.removeCli(sender);
	close(sender->getFd());
	delete sender;
}
