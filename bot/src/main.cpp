/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:08:27 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/16 18:33:00 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stdlib.h>
#include "Bot.hpp"
#include "Api.hpp"

int main(int ac, char *av[], char *envp[]) {
	(void)ac;
	(void)av;
	// if (ac != 3)
	// 	return std::cerr << "Usage: ./ircbot <server port> <server password>"
	// 					 << std::endl,
	// 		   1;
	// std::cout << ac << " | " << av[1] << " | " << av[2] << std::endl;
	
	// Bot &bot = Bot::getInstance(std::atoi(av[1]), av[2]);
	Api api(envp);

	if (!api.findSecret()) {
		std::cerr << "error: secret not found\n";
        return (false);
	}
	if (!api.generateToken())
		return (1);	
	if (!api.request(av[1])) {
		return (1);
	}
	std::cout << "post of "<< av[1] <<  ": " << api.getMess() << std::endl;
	return (0);
	// std::cout << &bot << std::endl;
}