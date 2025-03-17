/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:11:56 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/17 14:04:00 by aljulien         ###   ########.fr       */
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
	static Server &server = Server::GetServerInstance(atoi(av[1]), av[2]);
	server.servInit();
	server.servRun();

	/* 	for (channelMapIt it =
			 server.getAllChan().begin();
		 it != server.getAllChan().end(); ++it) {
		std::cout << "Channel: " << it->second->getName() << std::endl;
		for (clientMapIt itCli =
				 it->second->getCliInChan().begin();
			 itCli != it->second->getCliInChan().end(); ++itCli) {
			std::cout << "Client: " << itCli->second->getNick() << std::endl;
		}
	} */
	return (0);
}
