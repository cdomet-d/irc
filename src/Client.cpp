/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:28:52 by aljulien          #+#    #+#             */
/*   Updated: 2025/02/20 18:40:57 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <arpa/inet.h>
#include <cerrno>
#include <string.h>

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */

//TODO: Client-specific exceptions ?
Client::Client(int servFd, int epollFd)
	: len(sizeof(cliAddr)), addrIP(inet_ntoa(cliAddr.sin_addr))
{
	cliFd = accept(servFd, (sockaddr *)&cliAddr, &len);
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
	
	std::cout << "Client [" << cliFd << " ] connected from " << addrIP
			  << std::endl;
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */

/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */

const char *Client::InitFailed::what() const throw()
{
	std::cerr << "irc: ";
	return errMessage;
}

Client::InitFailed::InitFailed(const char *err) : errMessage(err) {}
