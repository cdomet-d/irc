/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:11:56 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/14 12:53:41 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <csignal>
#include <cstdlib>

int gSign = false;

void SignalHandler(int signum) {
	(void)signum;
	gSign = true;
}

int main(int ac, char **av) {
	if (ac != 3)
		return (std::cout << "Missing arguments (port and password)\n", 0);

	signal(SIGINT, SignalHandler);
	signal(SIGQUIT, SignalHandler);

	int port = atoi(av[1]);
	std::string password = av[2];
	std::cout << port << " | " << password << std::endl;
	Server &server = Server::GetServerInstance(port, password);
	server.servInit();
	server.servRun();
	return (0);
}
