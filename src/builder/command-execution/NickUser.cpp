/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickUser.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:46:19 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/10 10:12:24 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>

bool nickInUse(std::string newNickname, Client *curCli)
{
	log(DEBUG, "nickInUse");

	static Server &server = Server::GetServerInstance(gPort, gPassword);

	for (clientMapIt it = server.getAllCli().begin();
		 it != server.getAllCli().end(); ++it) {
		if (newNickname == it->second->getNick()) {
			sendReply(curCli->getFd(),
					  ERR_NICKNAMEINUSE(it->second->getNick(), newNickname));
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
	curCli->setPrefix();
	log(DEBUG, "getPrefix = ", curCli->getPrefix());
}
