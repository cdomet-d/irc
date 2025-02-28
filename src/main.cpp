/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:11:56 by aljulien          #+#    #+#             */
/*   Updated: 2025/02/28 16:24:19 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <csignal>
#include <cstdlib>

int gSign = false;
int gPort = 0;
std::string gPassword = "";

void SignalHandler(int signum)
{
	(void)signum;
	gSign = true;
}

int main(int ac, char **av)
{
	(void)av;
	if (ac != 3)
		return (std::cout << "Missing arguments (port and password)\n", 0);

	signal(SIGINT, SignalHandler);
	signal(SIGQUIT, SignalHandler);

	gPort = atoi(av[1]);
	gPassword = av[2];
	static Server &server = Server::GetInstanceServer(gPort, gPassword);
	server.servInit();
	server.servRun();
	std::map< int, Client * >::const_iterator allCli;
	for (allCli = server.getAllCli().begin(); allCli != server.getAllCli().end(); ++allCli) {
		std::cout << "Key: " << allCli->first
				  << ", Value (Client username): " << allCli->second->getUsername()
				  << std::endl;
	}

	std::map< std::string, Channel * >::const_iterator allChannel;
	for (allChannel = server.getAllCha().begin(); allChannel != server.getAllCha().end(); ++allChannel) {
		std::cout << "Key: " << allChannel->first
				  << ", Value (Channel name): " << allChannel->second->getName()
				  << std::endl;
		for (std::map< int, Client * >::iterator cli = allChannel->second->getAllCli().begin(); cli != allChannel->second->getAllCli().end(); ++cli)
			std::cout << "Client = " << cli->second->getNick(); 
	}
	return (0);
}