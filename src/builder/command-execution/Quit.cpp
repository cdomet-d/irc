/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 08:57:57 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/27 16:47:32 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    Client *sender = &cmd.getSender();
	sender->mess.clearMess();
	partAllChans(sender);
    checkOnlyOperator(sender->getFd());
	reply::send(sender->getFd(), RPL_BYEYBE());
	//server.disconnectCli(sender->getFd());
}