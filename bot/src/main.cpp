/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:08:27 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/15 17:23:46 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include "Reply.hpp"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

int main(int ac, char *av[]) {
	if (ac != 4)
		return std::cerr << "Usage: ./ircbot <server IP> <server port> <server "
							"password>"
						 << std::endl,
			   1;
	std::cout << av[1] << " | " << av[2] << " | " << av[3] << std::endl;

	try {
		Bot &bot = Bot::getInstance(std::atoi(av[1]), av[2], av[3]);
		bot.requestConnection();
		while (1) {
			RPL::send_(bot.getFd(), "Hi, I'm a bot\r\n");
			sleep(15);
		}
	} catch (std::runtime_error &e) { std::cerr << e.what() << std::endl; }
}