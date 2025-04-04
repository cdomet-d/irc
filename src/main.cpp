/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:11:56 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/04 13:39:41 by aljulien         ###   ########.fr       */
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
	if (ac != 3)
		return (std::cerr << "Expected <port> <password>" << std::endl, 1);

	signal(SIGINT, SignalHandler);
	signal(SIGQUIT, SignalHandler);
	int port = atoi(av[1]); //TODO: protect atoi from overflow
	std::string password = av[2];

	Server &server = Server::GetServerInstance(port, password);
	CmdManager &cmManager = CmdManager::getManagerInstance();

	cmManager.generateCmds();
	server.servInit();
	server.servRun();
	return (0);
}