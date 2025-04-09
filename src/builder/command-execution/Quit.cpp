/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 08:57:57 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/07 18:04:45 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "Server.hpp"
#include <sstream>

void
partAllChans (Client *sender) {
	std::vector< std::string > joinedChans = sender->getJoinedChans ();

	for (size_t nbChan = 0; nbChan != joinedChans.size (); nbChan++) {
		std::string tempMess = "PART " + joinedChans[nbChan] + "\n\r";
		sender->mess.setMess (tempMess);
		buffer_manip::prepareCommand (*sender);
	}
}

void
quit (CmdSpec &cmd) {
	Client *sender = &cmd.getSender ();
	sender->mess.clearMess ();
	partAllChans (sender);
	reply::send_ (sender->getFd (), RPL_BYEYBE (sender->cliInfo.getNick ()));
	std::stringstream ss;
	ss << "Client [" << sender->getFd () << "] disc";
	reply::log (reply::INFO, ss.str ());
	cmd.serv_.removeCli (sender);
	close (sender->getFd ());
	delete sender;
}
