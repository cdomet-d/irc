#include "Bot.hpp"
#include "Cmd.hpp"
#include "Reply.hpp"
#include <csignal>
#include <iostream>
#include <stdlib.h>

void sigHandler(int signum) {
	(void)signum;
	Bot &bot = Bot::getInstance(0, "", "");
	cmd::disconnect(bot);
	bot.setSignal(true);
}

int main(int ac, char *av[]) {
	if (ac != 4)
		return std::cerr
				   << "Usage: ./ircbot <server IP> <server port> <server "
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
			} else
				bot.executeCmd();
		}
	} catch (std::runtime_error &e) { std::cerr << e.what() << std::endl; }
	return 0;
}