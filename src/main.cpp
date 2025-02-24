/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:11:56 by aljulien          #+#    #+#             */
/*   Updated: 2025/02/24 15:50:42 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <csignal>
#include <cstdlib>

int sign = false;

void SignalHandler(int signum) {
	(void)signum;
	sign = true;
}

int main(int ac, char **av) {
	(void)av;
	if (ac != 3)
		return (std::cout << "Missing arguments (port and password)\n", 0);

	signal(SIGINT, SignalHandler);
	signal(SIGQUIT, SignalHandler);

	static Server &server = Server::GetInstanceServer(atoi(av[1]), av[2]);
	server.servInit();
	server.servRun();
	std::map<int, Client*>::const_iterator it;
	for (it = server._client.begin(); it != server._client.end(); ++it)
{
    std::cout << "Key: " << it->first << ", Value (Client fd): " << it->second->getUsername() << std::endl;
}

	return (0);
}