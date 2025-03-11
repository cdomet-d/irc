/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:11:56 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/11 10:57:01 by cdomet-d         ###   ########.fr       */
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

int main(int ac, char **av) {
	(void)av;
	if (ac != 3)
		return (std::cout << "Missing arguments (port and password)\n", 0);

	signal(SIGINT, SignalHandler);
	signal(SIGQUIT, SignalHandler);

	gPort = atoi(av[1]);
	gPassword = av[2];
	static Server &server = Server::GetServerInstance(gPort, gPassword);
	server.servInit();
	server.servRun();

	for (channelMapIt it =
			 server.getAllChan().begin();
		 it != server.getAllChan().end(); ++it) {
		std::cout << "Channel: " << it->second->getName() << std::endl;
		for (clientMapIt itCli =
				 it->second->getCliInChan().begin();
			 itCli != it->second->getCliInChan().end(); ++itCli) {
			std::cout << "Client: " << itCli->second->getNick() << std::endl;
		}
	}
	return (0);
}

// #include <iostream>
// #include "CommandManager.hpp"
// #include "Client.hpp"

// int	main(int argc, char** argv)
// {
// 	(void)argc;
// 	Client			client;
// 	std::string		buffer = "JOIN #pizza,#bitch,prout key1,key2 other shit";//argv[1]
// 	CommandManager	cmManager;
// 	size_t			i = 0;
// 	std::string		cm;

// 	client.setRegistration(3);
	
// 	//create the map with all registered commands
// 	cmManager.generateCmds();

// 	//execute command
// 	i = buffer.find(" ");
// 	if (i == std::string::npos)
// 		i = buffer.size() - 1;
// 	cm.assign(buffer, 0, i);
// 	buffer.erase(0, i + 1);
// 	cmManager.executeCm(cmManager.getCmd(cm).process(buffer, client));
// }