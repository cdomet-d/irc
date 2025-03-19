/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:11:56 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/19 13:07:40 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdManager.hpp"
#include "Server.hpp"
#include <csignal>
#include <cstdlib>
#include <sstream>

int gSign = false;

void SignalHandler(int signum) {
	(void)signum;
	gSign = true;
}

int main(int ac, char *av[]) {
	if (ac < 3) {
		std::cerr << "Expected <port> <password>" << std::endl;
		return 1;
	}

	signal(SIGINT, SignalHandler);
	signal(SIGQUIT, SignalHandler);

	int port = atoi(av[1]);
	std::string password = av[2];
	Server &server = Server::GetServerInstance(port, password);
	CmdManager &cmManager = CmdManager::getManagerInstance();
	cmManager.generateCmds();
	server.servInit();
	server.servRun();
	// Client cli;
	// cli.cliInfo.setRegistration(3);
	// std::string input;
	// while(1) {
	// 	std::getline(std::cin, input);
	// 	if (std::cin.eof())
	// 		return (1);
	// 	cli.mess.setBuffer(input);
	// 	messageValidator::assess(cli);

	// }

	return (0);
}
