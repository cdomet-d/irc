/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:11:56 by aljulien          #+#    #+#             */
/*   Updated: 2025/02/20 10:41:16 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <csignal>
#include <cstdlib>

int sign = false;

void SIgnalHandler(int signum)
{
	(void)signum;
	sign = true;
}

int main(int ac, char **av)
{
	(void)av;
	if (ac != 3)
		return (std::cout << "Missing arguments (port and password)\n", 0);

	signal(SIGINT, SIgnalHandler);
	signal(SIGQUIT, SIgnalHandler);

	Server *server = Server::GetInstanceServer(atoi(av[1]), av[2]);
	server->servInit();
	server->servRun();
	return (0);
}