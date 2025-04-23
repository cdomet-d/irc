/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:02:54 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/23 15:25:44 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <iostream>
#include <map>
#include <signal.h>
#include <arpa/inet.h>
#include <fstream>
#include <netinet/in.h>
#include <string>

bool gSign = false;

class Bots {
	public :
		int sockFd;
		struct sockaddr_in serv_;
};

void sigHandler(int signum) {
	(void)signum;
	gSign = true;
}

int main() {
	
	struct sigaction sa;
	sa.sa_handler = sigHandler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);

	std::map<std::string, int>clients;

	for (int i  = 0; i < 1000; i++) {
		Bots *bot = new Bots();
		bot->sockFd = socket(AF_INET, SOCK_STREAM, 0);
		int res = connect(bot->sockFd, (const struct sockaddr *)&bot->serv_, sizeof(bot->serv_));
		if (res != -1)
			std::cout << "bot " << i << " connected" << std::endl;
		send()
	}
	return (0);
}