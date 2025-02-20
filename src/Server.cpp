/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:39 by aljulien          #+#    #+#             */
/*   Updated: 2025/02/20 10:40:08 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server *Server::_server = NULL;

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */

Server::Server(int port, std::string password)
	: _port(port), _password(password)
{
}

Server::Server(void) : _port(0), _password("") {}

Server::~Server(void) {}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */

//TODO : need to determine is false means the function work or something went wrong
bool Server::servInit()
{
	int en = 1;

	_epollFd = epoll_create1(0);
	if (_epollFd == -1)
		return (false);
	_servAddress.sin_family = AF_INET;
	_servAddress.sin_port = htons(_port);
	_servAddress.sin_addr.s_addr = INADDR_ANY;

	_servFd = socket(AF_INET, SOCK_STREAM, 0);

	if (setsockopt(_servFd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) == -1)
		return (false);
	if (fcntl(_servFd, F_SETFL) == -1)
		return (false);
	if (bind(_servFd, (struct sockaddr *)&_servAddress, sizeof(_servAddress)) ==
		-1)
		return (false);
	if (listen(_servFd, SOMAXCONN) == -1)
		return (false);
	_servPoll.data.fd = _servFd;
	_servPoll.events = POLLIN;
	if (epoll_ctl(_epollFd, EPOLL_CTL_ADD, _servFd, &_servPoll) == -1)
		return 0;
	return (true);
}

bool Server::servRun()
{
	int nbFds;

	std::cout << "Server listening on port " << _port << std::endl;
	while (sign == false) {
		nbFds = epoll_wait(_epollFd, _events, MAX_EVENTS, -1);
		if (nbFds == -1 && sign == false)
			return (false);
		for (int i = 0; i < nbFds; i++) {
			if (_events[i].data.fd == _servFd)
				acceptClient();
		}
	}
	return (true);
}

//TODO : need to declare sockaddr_in struct, int incomingFd and epoll_event struct for each incoming clients
//so needs to be in the client class
bool Server::acceptClient()
{
	struct sockaddr_in cliAddr;
	struct epoll_event cliEpoll;
	int cliFd;
	socklen_t len;
	std::string addrIP;

	len = sizeof(cliAddr);
	cliFd = accept(_servFd, (sockaddr *)&cliAddr, &len);
	if (cliFd == -1)
		return (false);
	if (fcntl(cliFd, F_SETFL, O_NONBLOCK) == -1)
		return (close(cliFd), false);
	cliEpoll.events = EPOLLIN;
	cliEpoll.data.fd = cliFd;
	if (epoll_ctl(_epollFd, EPOLL_CTL_ADD, cliFd, &cliEpoll) == -1)
		return (close(cliFd), false);
	addrIP = inet_ntoa(cliAddr.sin_addr);
	std::cout << "Client <" << cliFd << "> connected from " << addrIP
			  << std::endl;
	return (true);
}

Server *Server::GetInstanceServer(int port, std::string password)
{
	if (_server == NULL)
		_server = new Server(port, password);
	return (_server);
}
