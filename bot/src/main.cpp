/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:08:27 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/25 14:28:52 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include "Cmd.hpp"
#include "Reply.hpp"
#include <csignal>
#include <iostream>
#include <limits>

void sigHandler(int signum) {
	(void)signum;
	Bot &bot = Bot::getInstance(0, "", "", NULL);
	cmd::disconnect(bot);
	bot.setSignal(true);
}

static double getPort(char *sPort) {
	char *endptr;
	errno = 0;
	double res = std::strtod(sPort, &endptr);

	if (errno == ERANGE || *endptr != '\0' || res < 0 ||
		res > std::numeric_limits< int >::max())
		return (-1);
	if (res <= 6664 || res >= 6670)
		return (-1);
	return (res);
}

int main(int ac, char *av[], char *envp[]) {
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
		double port = getPort(av[2]);
		if (port == -1)
			return std::cerr << "Invalid port" << std::endl, 1;
		Bot &bot = Bot::getInstance(port, av[3], av[1], envp);
		if (!bot.registrationSequence())
			return 1;
		while (bot.getSignal() == false) {
			ssize_t bytes = bot.receive();
			if (bytes == -1 && errno == EINTR)
				break;
			if (bytes == 0) {
				if (!bot.registrationSequence())
					return 1;
			} else
				bot.executeCmd();
		}
	} catch (std::runtime_error &e) { std::cerr << e.what() << std::endl; }
	return 0;
}