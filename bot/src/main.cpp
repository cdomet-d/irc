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
#include <csignal>
#include "Bot.hpp"
#include "Api.hpp"
#include "Reply.hpp"

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

	struct sigaction sa;
	sa.sa_handler = sigHandler;
	sigemptyset(&sa.sa_mask);
	// disables SA_RESTART so that recv doesn't block SIGINT, even in its current blocking mode;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);

	try {
		Bot &bot = Bot::getInstance(std::atoi(av[2]), av[3], av[1]);
		if (!bot.registrationSequence())
			return 1;
		while (bot.getSignal() == false) {
			ssize_t bytes = bot.receive();
			if (bytes == -1 && errno == EINTR)
				break;
			if (bytes == 0) {
				if (!bot.registrationSequence())
					return 1;
			}
			bot.executeCmd();
		}
	} catch (std::runtime_error &e) { std::cerr << e.what() << std::endl; }
	RPL::log(RPL::INFO, "Bye!");
	return 0;
	/*Api api(envp);

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
	return (0);*/
}