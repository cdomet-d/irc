/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickUserParsing.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:22:45 by aljulien          #+#    #+#             */
/*   Updated: 2025/02/25 16:51:24 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool handleNick(std::string buffer, int fd)
{
	std::vector< std::string > inputCli = VectorSplit(buffer, "\n");
	static Server &server = Server::GetInstanceServer(gPort, gPassword);
	for (std::vector< std::string >::iterator it = inputCli.begin();
		 it != inputCli.end(); ++it) {
		if (it->find("NICK") != it->npos) {
			std::string nick = findNick(*it);
			std::map< int, Client * >::iterator whatCli =
				server._client.find(fd);
			whatCli->second->setNick(nick);
			log(DEBUG, whatCli->second->getNick());
		}
	}
	return (true);
}

bool handleUsername(std::string buffer, int fd)
{
	std::vector< std::string > inputCli = VectorSplit(buffer, "\n");
	static Server &server = Server::GetInstanceServer(gPort, gPassword);
	for (std::vector< std::string >::iterator it = inputCli.begin();
		 it != inputCli.end(); ++it) {
		if (it->find("USER") != it->npos) {
			std::string user = findUsername(*it);
			std::map< int, Client * >::iterator whatCli =
				server._client.find(fd);
			whatCli->second->setUsername(user);
			log(DEBUG, whatCli->second->getUsername());
		}
	}
	return (true);
}

std::string findNick(std::string &buffer)
{
	log(DEBUG, "-----handleNick-----");

	if (buffer.find("NICK") != buffer.npos)
		buffer.erase(buffer.find("NICK"), 5);
	return (buffer);
}

std::string findUsername(std::string &buffer)
{
	log(DEBUG, "-----handleUser-----");

	std::string user;
	if (buffer.find("USER") != buffer.npos)
		buffer.erase(buffer.find("USER"), 5);
	std::string::iterator it = buffer.begin();
	for (; *it != ' '; ++it)
		user.push_back(*it);
	return (user);
}