/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickUser.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:46:19 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/06 16:30:57 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>

bool nickInUse(std::string newNickname, Client *currentCli) {
	log(DEBUG, "nickInUse");

	static Server &server = Server::GetInstanceServer(gPort, gPassword);
	
	for (std::map<int, Client *>::iterator it = server.getAllCli().begin();
		it != server.getAllCli().end(); ++it) {
		if (newNickname == it->second->getNick()) {
  			sendReply(currentCli->getFd(), ERR_NICKNAMEINUSE(it->second->getNick(), newNickname));
			return (false);
		}
	}
	return (true);
}

void handleClientRegistration(const std::string& input, Client *currentCli) {
	std::istringstream iss(input);
    std::string line;
	
    while (std::getline(iss, line)) {
        if (line.find("CAP LS") != std::string::npos) {
			continue ;
		} else if (line.find("NICK") != std::string::npos) {
            std::string nick;
            std::istringstream nickStream(line);
            nickStream >> nick >> nick;
			if (nickInUse(nick, currentCli))
				currentCli->setNick(nick);
			log(DEBUG, "nick = ", currentCli->getNick());
        } else if (line.find("USER") != std::string::npos) {
            std::string username, mode, unused, realname;
            std::istringstream userStream(line);
            userStream >> username >> username >> mode >> unused;
            std::getline(userStream, realname);
			currentCli->setUsername(username);
			log(DEBUG, "username = ", username);
		}
    }
	currentCli->setPrefix();
	log(DEBUG, "getPrefix = ", currentCli->getPrefix());
}
