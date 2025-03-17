/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickUser.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:46:19 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/17 14:03:32 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>

bool nickInUse(std::string newNick, Client *curCli)
{
	log(DEBUG, "nickInUse");

	static Server &server = Server::GetServerInstance(0, "");

	for (clientMapIt it = server.getAllCli().begin();
		 it != server.getAllCli().end(); ++it) {
		if (newNick == it->second->getNick()) {
			sendReply(curCli->getFd(),
					  ERR_NICKNAMEINUSE(it->second->getNick()));
			return (false);
		}
	}
	return (true);
}

void handleClientRegistration(const std::string &input, Client *curCli)
{
	std::istringstream iss(input);
	std::string line;

	while (std::getline(iss, line)) {
		if (line.find("CAP LS") != std::string::npos) {
			continue;
		} else if (line.find("PASS") != std::string::npos) {
			std::string pass;
			std::istringstream passStream(line);
			passStream >> pass >> pass;
			handlePass(pass, curCli);
		} else if (line.find("NICK") != std::string::npos) {
			std::string nick;
			std::istringstream nickStream(line);
			nickStream >> nick >> nick;
			if (nickInUse(nick, curCli))
				curCli->setNick(nick);
			log(DEBUG, "nick = ", curCli->getNick());
		} else if (line.find("USER") != std::string::npos) {
			std::string username, mode, unused, realname;
			std::istringstream userStream(line);
			userStream >> username >> username >> mode >> unused;
			std::getline(userStream, realname);
			curCli->setUsername(username);
			log(DEBUG, "username = ", username);
		}
	}
	if (curCli->getNick().empty() == false &&
		curCli->getUsername().empty() == false)
		sendReply(curCli->getFd(), REG_COMPLETE());
	curCli->setPrefix();
	log(DEBUG, "getPrefix = ", curCli->getPrefix());
}