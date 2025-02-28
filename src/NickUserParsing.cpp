/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickUserParsing.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:22:45 by aljulien          #+#    #+#             */
/*   Updated: 2025/02/28 10:41:41 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool handleNick(std::vector< std::string > inputCli, int fd)
{
	//log(DEBUG, "-----handleNick-----");
	static Server &server = Server::GetInstanceServer(gPort, gPassword);
	for (std::vector< std::string >::iterator it = inputCli.begin();
		 it != inputCli.end(); ++it) {
		if (it->find("NICK") != it->npos) {
			std::string nick = findNick(*it);
			std::map< int, Client * >::iterator whatCli =
				server.getAllCli().find(fd);
			whatCli->second->setNick(nick);
			//log(DEBUG, "NICKNAME = ", whatCli->second->getNick());
			return (true);
		}
	}
	return (false);
}

bool handleUsername(std::vector< std::string > inputCli, int fd)
{
	//log(DEBUG, "-----handleUsername-----");
	static Server &server = Server::GetInstanceServer(gPort, gPassword);
	for (std::vector< std::string >::iterator it = inputCli.begin();
		 it != inputCli.end(); ++it) {
		if (it->find("USER") != it->npos) {
			std::string user = findUsername(*it);
			std::map< int, Client * >::iterator whatCli =
				server.getAllCli().find(fd);
			whatCli->second->setUsername(user);
			//log(DEBUG, "USERNAME = ", whatCli->second->getUsername());
			return (true);
		}
	}
	return (false);
}

std::string findNick(std::string &buffer)
{
	std::string nick;
	if (buffer.find("NICK") != buffer.npos)
		buffer.erase(buffer.find("NICK"), 5);
	for (std::string::iterator it = buffer.begin(); it != buffer.end() && *it != ' ' && *it != '\n' && *it != '\r'; ++it)
		nick.push_back(*it);
	return (nick);
}

std::string findUsername(std::string &buffer)
{
	std::string user;
	if (buffer.find("USER") != buffer.npos)
		buffer.erase(buffer.find("USER"), 5);
	for (std::string::iterator it = buffer.begin();
		 it != buffer.end() && *it != ' '; ++it)
		user.push_back(*it);
	return (user);
}