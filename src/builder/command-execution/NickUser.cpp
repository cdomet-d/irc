/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickUser.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:46:19 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/06 13:55:53 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>

bool nickInUse(std::string newNickname, int fd) {
	log(DEBUG, "nickInUse");
	static Server &server = Server::GetInstanceServer(gPort, gPassword);

	for (clientMapIt it = server.getAllCli().begin();
		 it != server.getAllCli().end(); ++it) {
		if (newNickname == it->second->getNick()) {
			sendReply(fd,
					  ERR_NICKNAMEINUSE(it->second->getNick(), newNickname));
			return (false);
		}
	}
	return (true);
}

void handleClientRegistration(const std::string &input, int cliFd,
							  clientMap &registeredClients) {
	std::istringstream iss(input);
	std::string line;
	clientMapIt curClient = registeredClients.find(cliFd);

	while (std::getline(iss, line)) {
		if (line.find("CAP LS") != std::string::npos) {
			continue;
		} else if (line.find("NICK") != std::string::npos) {
			std::string nick;
			std::istringstream nickStream(line);
			nickStream >> nick >> nick;
			if (nickInUse(nick, cliFd))
				curClient->second->setNick(nick);
			log(DEBUG, "nick: ", curClient->second->getNick());
		} else if (line.find("USER") != std::string::npos) {
			std::string username, mode, unused, realname;
			std::istringstream userStream(line);
			userStream >> username >> username >> mode >> unused;
			std::getline(userStream, realname);
			curClient->second->setUsername(username);
			log(DEBUG, "username: ", username);
		}
	}
	curClient->second->setPrefix();
	log(DEBUG, "getPrefix: ", curClient->second->getPrefix());
}
