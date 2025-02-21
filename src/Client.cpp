/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:28:52 by aljulien          #+#    #+#             */
/*   Updated: 2025/02/21 14:30:00 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <arpa/inet.h>
#include <cerrno>
#include <string.h>

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */
// WARN: still not sure wether we need the client IP adress or not
Client::Client(int servFd, int epollFd)
{
	cliFd = accept(servFd, NULL, 0);
	if (cliFd == -1)
		throw Client::InitFailed(const_cast< const char * >(strerror(errno)));
	if (fcntl(cliFd, F_SETFL, O_NONBLOCK) == -1) {
		close(cliFd);
		throw Client::InitFailed(const_cast< const char * >(strerror(errno)));
	}
	cliEpoll.events = EPOLLIN;
	cliEpoll.data.fd = cliFd;
	if (epoll_ctl(epollFd, EPOLL_CTL_ADD, cliFd, &cliEpoll) == -1) {
		close(cliFd);
		throw Client::InitFailed(const_cast< const char * >(strerror(errno)));
	}
	std::cout << "Client [" << cliFd << "] connected " << std::endl;
}

Client::~Client() {}
Client::Client(const Client &rhs)
{
	static_cast< void >(rhs);
}
Client::Client(void) {}
Client &Client::operator=(const Client &rhs)
{
	static_cast< void >(rhs);
	return *this;
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */
int Client::getFd() const
{
	return cliFd;
}

std::string Client::getName() const
{
	return _name;
}
std::string Client::getNick() const
{
	return _nick;
}
std::string Client::getRealName() const
{
	return _realName;
}
bool Client::getOpStatus() const
{
	return _isOp;
}

/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */

const char *Client::InitFailed::what() const throw()
{
	std::cerr << "irc: ";
	return errMessage;
}

Client::InitFailed::InitFailed(const char *err) : errMessage(err) {}
