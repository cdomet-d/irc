/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:11:56 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/23 14:02:12 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdManager.hpp"
#include "Server.hpp"
#include <csignal>
#include <cstdlib>
#include <sstream>
#include <limits>

int gSign = false;

void SignalHandler(int signum) {
	(void)signum;
	gSign = true;
}

double getPort(char *sPort) {
	char *endptr;
	errno = 0;
	double result = std::strtod(sPort, &endptr);

	if (errno == ERANGE || *endptr != '\0' || result < 0
		|| result > std::numeric_limits< int >::max())
		return (-1);
	return (result);			
}

int main(int ac, char *av[]) {
	if (ac != 3)
		return (std::cerr << "Expected <port> <password>" << std::endl, 1);

	signal(SIGINT, SignalHandler);
	signal(SIGQUIT, SignalHandler);
	
	int port = getPort(av[1]);
	std::string password = av[2];

	Server &server = Server::GetServerInstance(port, password);
	CmdManager &cmManager = CmdManager::getManagerInstance();

	cmManager.generateCmds();
	server.servInit();
	server.servRun();
	return (0);
}