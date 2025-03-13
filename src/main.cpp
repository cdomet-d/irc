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

#include "../client/Client.hpp"
#include "CmdManager.hpp"
#include <iostream>

int main(int argc, char **argv) {
	Client client;
	std::vector< std::string > buffer;
	CmdManager cmManager;

	if (argc < 2)
		return (1);
	for (size_t i = 2; i < argc; i++) {
		buffer.push_back(argv[i]);
	}
	client.cliInfo.setRegistration(3);

	//create the map with all registered commands
	cmManager.generateCmds();

	//execute command
	try {
		cmManager.executeCm(cmManager.getCmd(argv[1]).process(buffer, client));
	} catch (const CmdManager::CmdNotFoundException &e) {
		std::cout << ERR_UNKNOWNCOMMAND(client.cliInfo.getNick(), argv[1]);
	}
}