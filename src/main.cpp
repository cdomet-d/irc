/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:11:56 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/17 14:20:45 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdManager.hpp"
#include "Server.hpp"
#include <csignal>
#include <cstdlib>

int gSign = false;

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

	CmdManager &cmManager = CmdManager::getManagerInstance();
	cmManager.generateCmds();

	int port = atoi(av[1]);
	std::string password = av[2];
	std::cout << port << " | " << password << std::endl;
	Server &server = Server::GetServerInstance(port, password);
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

// int main(int argc, char **argv) {
// 	Client client;
// 	CmdManager &cmManager = CmdManager::getManagerInstance();

// 	if (argc < 2) {
// 		std::cerr << "not enough params\n";
// 		return (1);
// 	}

// 	client.cliInfo.setRegistration(3);
// 	client.mess.setBuffer(argv[1]);

// 	cmManager.generateCmds();

// 	MessageValidator::assess(client);
// 	return (0);
// }
