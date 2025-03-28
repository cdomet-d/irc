/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 08:57:57 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/28 12:53:00 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "Server.hpp"
#include <sstream>

void partAllChans(Client *sender) {
	for (stringVec::iterator currChanName = sender->getJoinedChans().begin();
		 currChanName != sender->getJoinedChans().end(); ++currChanName) {
		std::string tempMess = "PART " + *currChanName + "\n\r";
		sender->mess.setBuffer(tempMess);
		formatMess::assess(*sender);
	}
	sender->getJoinedChans().clear();
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
