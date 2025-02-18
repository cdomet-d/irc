/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:11:56 by aljulien          #+#    #+#             */
/*   Updated: 2025/02/18 17:59:48 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arpa/inet.h>
#include <csignal>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <poll.h>
#include <stdbool.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <vector>

const int MAX_EVENTS = 1000;
bool sign = false; //global for signal listening

void SIgnalHandler(int signum)
{
	(void)signum;
	sign = true;
}

void AcceptClient(int servSocketFd, int epollfd)
{
	struct sockaddr_in cliadd;
	socklen_t len = sizeof(cliadd);

	int incofd = accept(servSocketFd, (sockaddr *)&(cliadd), &len);
	if (incofd == -1) {
		std::cerr << "accept() failed" << std::endl;
		return;
	}

	if (fcntl(incofd, F_SETFL, O_NONBLOCK) == -1) {
		std::cerr << "fcntl() failed" << std::endl;
		close(incofd);
		return;
	}

	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = incofd;
	if (epoll_ctl(epollfd, EPOLL_CTL_ADD, incofd, &ev) == -1) {
		std::cerr << "epoll_ctl() failed" << std::endl;
		close(incofd);
		return;
	}

	std::string IPadd = inet_ntoa(cliadd.sin_addr);
	std::cout << "Client <" << incofd << "> Connected from " << IPadd
			  << std::endl;
}

int servInit()
{
	int port = 4444;  //port of th server
	int servSocketFd; //fds of the server
	struct sockaddr_in address;
	struct epoll_event newPoll;
	struct epoll_event events[MAX_EVENTS];

	int epollfd = epoll_create1(0);
	if (epollfd == -1)
		return 0;
	//std::vector< struct pollfd > fds; //vector for fds

	//int representing the address family (IPv4 or IPv6)
	address.sin_family = AF_INET;

	//16-bit int representing port number stored as big-endian. Function htons used for conversions
	address.sin_port = htons(port);

	//struct in_addr containing the IPv4 address.
	//The single member of the struct represents
	//the IPv4 address in network byte order.
	//The INADDR_ANY means any IP address, meaning
	//the socket will be bound to all available network interfaces on the host
	address.sin_addr.s_addr = INADDR_ANY;

	//We create a socket using the socket function
	//First parameter : int domains, specifies the communication domain. AF_INET is for IPv4 communication
	//Second parameter : int type, specifies the type of communication semantics for the socket. SOCK_STREAM is for TCP sockets
	//Third parameter : int protocol, speficies the protocol to be used with the socket, usually set to 0.
	servSocketFd = socket(AF_INET, SOCK_STREAM, 0);

	//setsockopt is used to set options on sockets to control the behavior of the socket
	//First paramter : the fd of the socket
	//Second parameter : int level, indicate the protocol level at which the optiens resides.
	//SOL_SOCKET indicates the options should only be applied to the current socket
	//Thrird parameter : int optname, SO_REUSEADDR option allow for the immediate reuse of local addresses and ports
	//Fourth parameter : pointer to the value that needs to be set for the option
	//Fifth parameter : size of the option value in bytes. Seting the value at 1 means the value is enabled
	int en = 1;
	if (setsockopt(servSocketFd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) ==
		-1)
		return (0);

	//Function is used to perform control operations on fds. Here it's used to set O_NONBLOCK flag on the server socket fd
	if (fcntl(servSocketFd, F_SETFL) == -1)
		return (0);

	//Function bind enables you to assign a specific address and port to a socket, providing it with a unique identity in the network
	//Here it's being bind to a IP address but it can also be bind to a hostname
	if (bind(servSocketFd, (struct sockaddr *)&address, sizeof(address)) == -1)
		return (0);

	//Function listen set the socket as a passive (server-side connection) socket ready to accept incoming connections.
	//SOMAXCONN refers to the max lenght of the queue of pending connections
	if (listen(servSocketFd, SOMAXCONN) == -1)
		return (0);

	//we initiliaze the newPoll to the server socket
	//It's needed because we will check the socket of the server for new connection
	// and the clients sockets for incoming data.
	// Adding the server socket to the loop of the poll() function is necessary to detect new connections.
	newPoll.data.fd = servSocketFd;
	newPoll.events = POLLIN;
	if (epoll_ctl(epollfd, EPOLL_CTL_ADD, servSocketFd, &newPoll) == -1)
		return 0;
	//newPoll.revents = 0;
	//fds.push_back(newPoll);

	std::cout << "Server listening on port " << port << std::endl;
	while (sign == false) {
		int nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
		if (nfds == -1 && sign == false)
			return 0;
		for (int i = 0; i < nfds; i++) {
			if (events[i].data.fd == servSocketFd)
				AcceptClient(servSocketFd, epollfd);
		}
		return (0);
	}

	int main()
	{
		signal(SIGINT, SIgnalHandler);
		signal(SIGQUIT, SIgnalHandler);
		servInit();
		return (0);
	}