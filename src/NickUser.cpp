/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickUser.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:46:19 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/04 18:19:10 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>

bool nickInUse(std::string newNickname, int fd) {
	log(DEBUG, "nickInUse");
	static Server &server = Server::GetInstanceServer(gPort, gPassword);
	
	for (std::map<int, Client *>::iterator it = server.getAllCli().begin();
		it != server.getAllCli().end(); ++it) {
		if (newNickname == it->second->getNick()) {
  			sendReply(fd, ERR_NICKNAMEINUSE(it->second->getNick(), newNickname));
			return (false);
		}
	}
	return (true);
}

void handleClientRegistration(const std::string& input, int fd) {
	static Server &server = Server::GetInstanceServer(gPort, gPassword);

	std::istringstream iss(input);
    std::string line;
	std::map<int, Client *>::iterator registerCli = server.getAllCli().find(fd);
	
    while (std::getline(iss, line)) {
        if (line.find("CAP LS") != std::string::npos) {
			continue ;
		} else if (line.find("NICK") != std::string::npos) {
            std::string nick;
            std::istringstream nickStream(line);
            nickStream >> nick >> nick;
			if (nickInUse(nick, fd))
				registerCli->second->setNick(nick);
			log(DEBUG, "nick = ", registerCli->second->getNick());
        } else if (line.find("USER") != std::string::npos) {
            std::string username, mode, unused, realname;
            std::istringstream userStream(line);
            userStream >> username >> username >> mode >> unused;
            std::getline(userStream, realname);
			registerCli->second->setUsername(username);
			log(DEBUG, "username = ", username);
			
		}
    }
	registerCli->second->setPrefix();
	log(DEBUG, "getPrefix = ", registerCli->second->getPrefix());
}
