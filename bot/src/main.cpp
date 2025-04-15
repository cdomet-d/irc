/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:08:27 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/14 15:35:57 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stdlib.h>
#include "Bot.hpp"

int main(int ac, char *av[]) {
	if (ac != 3)
		return std::cerr << "Usage: ./ircbot <server port> <server password>"
						 << std::endl,
			   1;
	std::cout << ac << " | " << av[1] << " | " << av[2] << std::endl;
	
	Bot &bot = Bot::getInstance(std::atoi(av[1]), av[2]);
	
	std::cout << &bot << std::endl;
}