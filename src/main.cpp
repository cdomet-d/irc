/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:11:56 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/17 18:26:46 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdManager.hpp"
#include "Server.hpp"
#include <csignal>
#include <cstdlib>

int gSign = false;

void SignalHandler(int signum) {
	(void)signum;
	gSign = true;
}

// int main(int ac, char **av) {
// 	if (ac != 3)
// 		return (std::cout << "Missing arguments (port and password)\n", 0);

// 	signal(SIGINT, SignalHandler);
// 	signal(SIGQUIT, SignalHandler);

// 	int port = atoi(av[1]);
// 	std::string password = av[2];
// 	std::cout << port << " | " << password << std::endl;
// 	Server &server = Server::GetServerInstance(port, password);
// 	server.servInit();
// 	CmdManager &cmManager = CmdManager::getManagerInstance();
// 	cmManager.generateCmds();
// 	server.servRun();
// 	return (0);
// }

int main(int argc, char **argv) {
	Client client;
	CmdManager &cmManager = CmdManager::getManagerInstance();

	if (argc < 2) {
		std::cerr << "not enough params\n";
		return (1);
	}

	Server &server = Server::GetServerInstance(6667, "hello");
	client.cliInfo.setRegistration(0);
	client.mess.setBuffer(argv[1]);

	cmManager.generateCmds();

	MessageValidator::assess(client);
	return (0);
}
