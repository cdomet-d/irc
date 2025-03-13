/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:11:56 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/13 10:17:23 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdManager.hpp"
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

// int main(int ac, char **av) {
// 	(void)av;
// 	if (ac != 3)
// 		return (std::cout << "Missing arguments (port and password)\n", 0);

// 	signal(SIGINT, SignalHandler);
// 	signal(SIGQUIT, SignalHandler);

// 	static CmdManager &cmManager = CmdManager::getManagerInstance();
// 	cmManager.generateCmds();

// 	gPort = atoi(av[1]);
// 	gPassword = av[2];
// 	static Server &server = Server::GetServerInstance(gPort, gPassword);
// 	server.servInit();
// 	server.servRun();

// 	for (channelMapIt it =
// 			 server.getAllChan().begin();
// 		 it != server.getAllChan().end(); ++it) {
// 		std::cout << "Channel: " << it->second->getName() << std::endl;
// 		for (clientMapIt itCli =
// 				 it->second->getCliInChan().begin();
// 			 itCli != it->second->getCliInChan().end(); ++itCli) {
// 			std::cout << "Client: " << itCli->second->cliInfo.getNick() << std::endl;
// 		}
// 	}
// 	return (0);
// }


int main(int argc, char **argv) {
	Client client;
	static CmdManager &cmManager = CmdManager::getManagerInstance();

	if (argc < 2) {
		std::cerr << "not enough params\n";
		return (1);
	}

	client.cliInfo.setRegistration(3);
	client.mess.setBuffer(argv[1]);

	cmManager.generateCmds();

	MessageValidator::assess(client);
	return (0);
}