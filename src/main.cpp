/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:11:56 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/12 18:00:09 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <csignal>
#include <cstdlib>

int gSign = false;
int gPort = 0;
std::string gPassword = "";

void SignalHandler(int signum) {
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
// 			std::cout << "Client: " << itCli->second->getNick() << std::endl;
// 		}
// 	}
// 	return (0);
// }

#include <iostream>
#include "CmdManager.hpp"
#include "Client.hpp"

int	main(int argc, char** argv)
{
	(void)argc;
	Client			client;
	std::vector<std::string>	buffer;
	CmdManager	cmManager;
	size_t			i = 0;
	std::string		cm;

	client.setRegistration(3);
	
	//create the map with all registered commands
	cmManager.generateCmds();

	//execute command
	// buffer.push_back("chacham");
	buffer.push_back("#pizza,#bitch,prout");
	buffer.push_back("key1,key2");
	cmManager.executeCm(cmManager.getCmd("JOIN").process(buffer, client));
}