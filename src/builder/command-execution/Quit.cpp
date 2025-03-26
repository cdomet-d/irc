/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 08:57:57 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/26 13:10:23 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "Server.hpp"

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
	sender->mess.clearBuffer();
	partAllChans(sender);
	reply::send(sender->getFd(), RPL_BYEYBE());
	std::stringstream ss;
	ss << "Client [" << sender->getFd() << "] deconnected";
	std::cout << ss << std::endl;
	reply::log(reply::INFO, ss.str());
	delete sender;
	server.removeCli(sender);
	close(sender->getFd());
}
