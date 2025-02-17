/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:11:56 by aljulien          #+#    #+#             */
/*   Updated: 2025/02/17 17:18:55 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <poll.h>
#include <stdbool.h>
#include <csignal>
#include <vector>
#include <arpa/inet.h>
#include <iostream>

bool sign = false; //global for signal listening

void SIgnalHandler(int signum)
{
	(void)signum;
	sign = true;
}

void AcceptClient(int servSocketFd, std::vector<struct pollfd> fds)
{
	int Fd; //client file descriptor
	std::string IPadd; // client ip address
	struct sockaddr_in cliadd;
	struct pollfd NewPoll;
	socklen_t len = sizeof(cliadd);

	int incofd = accept(servSocketFd, (sockaddr *)&(cliadd), &len); // accept the new client
	if (incofd == -1)
		{std::cout << "accept() failed" << std::endl; return;}

	if (fcntl(incofd, F_SETFL, O_NONBLOCK) == -1) // set the socket option (O_NONBLOCK) for non-blocking socket
		{std::cout << "fcntl() failed" << std::endl; return;}

	NewPoll.fd = incofd; // add the client socket to the pollfd
	NewPoll.events = POLLIN; // set the event to POLLIN for reading data
	NewPoll.revents = 0; // set the revents to 0

	Fd = incofd; // set the client file descriptor
	IPadd = inet_ntoa((cliadd.sin_addr)); // convert the ip address to string and set it
	fds.push_back(NewPoll); // add the client socket to the pollfd

	std::cout << "Client <" << incofd << "> Connected" << std::endl;
}

int servInit()
{
	std::vector<struct pollfd> fds; //vector for fds of clients
	int port = 4444; //port of th server
	int servSocketFd; //fds of the server
	struct sockaddr_in address; 
	struct pollfd newPoll;

	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = INADDR_ANY;

	servSocketFd = socket(AF_INET, SOCK_STREAM, 0);
	
	int en = 1;
	if (setsockopt(servSocketFd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) == -1)
		return (0);
	if (fcntl(servSocketFd, F_SETFL) == -1)
		return 0;
	if (bind(servSocketFd, (struct sockaddr *)&address, sizeof(address)) == -1)
		return 0;
	if (listen(servSocketFd, SOMAXCONN) == -1)
		return 0;

	newPoll.fd = servSocketFd;
	newPoll.events = POLLIN;
	newPoll.revents = 0;

	fds.push_back(newPoll);
	std::cout << "Server listening on port " << port << std::endl;
	while (sign == false)
	{
		if ((poll(&fds[0],fds.size(),-1) == -1) && sign == false)
			return 0;
		for (size_t i = 0; i < fds.size(); i++) //check all fds
		{

			if (fds[i].revents & POLLIN)//check if there is data to read
			{
				if (fds[i].fd == servSocketFd)
					AcceptClient(servSocketFd, fds); //accept client
			}
		}
	}
	return 0;
}

int main ()
{
	signal(SIGINT, SIgnalHandler);
	signal(SIGQUIT, SIgnalHandler);
	servInit();
	return (0);	
}