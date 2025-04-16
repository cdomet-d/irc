/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:08:27 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/16 16:55:06 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include "Reply.hpp"
#include <csignal>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

void sigHandler(int signum) {
	(void)signum;
	Bot &bot = Bot::getInstance(0, "", "");
	bot.setSignal(true);
}

int main(int ac, char *av[]) {
	if (ac != 4)
		return std::cerr << "Usage: ./ircbot <server IP> <server port> <server "
							"password>"
						 << std::endl,
			   1;
	std::cout << av[1] << " | " << av[2] << " | " << av[3] << std::endl;

	signal(SIGINT, sigHandler);
	signal(SIGQUIT, sigHandler);

	try {
		Bot &bot = Bot::getInstance(std::atoi(av[2]), av[3], av[1]);
		if (!bot.registrationSequence())
			return 1;
		while (bot.getSignal() == false) {
			if (bot.receive() == 0) {
				if (!bot.registrationSequence())
					return 1;
			}
		}
	} catch (std::runtime_error &e) { std::cerr << e.what() << std::endl; }
	RPL::log(RPL::INFO, "Bye!");
	return 0;
}