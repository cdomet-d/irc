/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 08:57:57 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/25 13:34:30 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "Server.hpp"

void partAllChans(Client *sender) {
   static Server &server = Server::GetServerInstance(0, "");

    for (stringVec::iterator currChanName = sender->getJoinedChans().begin();
        currChanName != sender->getJoinedChans().end(); ++currChanName) {
			partOneChan(sender, *server.getAllChan().find(*currChanName)->second);
		}
	sender->getJoinedChans().clear();
}

void quit(CmdSpec &cmd) {
	static Server &server = Server::GetServerInstance(0, "");

    Client *sender = &cmd.getSender();
	sender->mess.clearBuffer();
	
	partAllChans(sender);
    checkOnlyOperator(sender->getFd());
	server.disconnectCli(sender->getFd());
}