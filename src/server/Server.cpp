/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:39 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/11 14:10:58 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <algorithm>
#include <cerrno>
#include <sstream>
#include <stdio.h>
#include <unistd.h>
#include <vector>

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */

Server::Server(int port, std::string password) : port_(port), pass_(password) {}
Server::Server(void) : port_(0), pass_("") {}

Server::~Server(void)
{
	std::cout << "Calling destructor" << std::endl;
	for (clientMapIt it = clients_.begin(); it != clients_.end(); ++it) {
		it->second->getNick().clear();
		it->second->getUsername().clear();
		close(it->first);
		delete it->second;
	}
	for (channelMapIt it = channels_.begin(); it != channels_.end();
		 ++it)
		delete it->second;

	close(epollFd_);
	close(servFd_);
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */

bool Server::servInit()
{
	int en = 1;

	epollFd_ = epoll_create1(0);
	if (epollFd_ == -1)
		return (false);
	servAddr_.sin_family = AF_INET;
	servAddr_.sin_port = htons(port_);
	servAddr_.sin_addr.s_addr = INADDR_ANY;

	servFd_ = socket(AF_INET, SOCK_STREAM, 0);

	if (setsockopt(servFd_, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) == -1)
		return (false);
	if (fcntl(servFd_, F_SETFL, O_NONBLOCK) == -1)
		return (false);
	if (bind(servFd_, (struct sockaddr *)&servAddr_, sizeof(servAddr_)) == -1)
		return (false);
	if (listen(servFd_, SOMAXCONN) == -1)
		return (false);
	servPoll_.data.fd = servFd_;
	servPoll_.events = POLLIN;
	if (epoll_ctl(epollFd_, EPOLL_CTL_ADD, servFd_, &servPoll_) == -1)
		return 0;
	// log(INFO, "IRC server initialized");
	return (true);
}

bool Server::servRun()
{
	int nbFds;

	// log(INFO, "Loop IRC server started");
	std::cout << "Server listening on port " << port_
			  << " | IP adress: " << inet_ntoa(servAddr_.sin_addr) << std::endl;
	while (gSign == false) {
		nbFds = epoll_wait(epollFd_, events_, MAX_EVENTS, -1);
		if (nbFds == -1 && gSign == false)
			return (false);
		for (int i = 0; i < nbFds; i++) {
			if (events_[i].data.fd == servFd_)
				acceptClient();
			else if (handleData(events_[i].data.fd) == false)
				return true;
		}
	}
	return (true);
}

void Server::acceptClient()
{
	try {
		// log(INFO, "Accepting new client");
		Client *newCli = new Client();
		struct epoll_event cliEpollTemp;
		socklen_t cliLen = sizeof(newCli->cliAddr_);
		newCli->setFd(
			accept(servFd_, (struct sockaddr *)&newCli->cliAddr_, &cliLen));

		if (newCli->getFd() == -1)
			throw Server::InitFailed(
				const_cast< const char * >(strerror(errno)));

		char client_ip[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &(newCli->cliAddr_.sin_addr), client_ip,
				  INET_ADDRSTRLEN);
		newCli->setIP(client_ip);

		char hostname[NI_MAXHOST];
		int result = getnameinfo((struct sockaddr *)&newCli->cliAddr_, cliLen,
								 hostname, NI_MAXHOST, NULL, 0, 0);
		if (result == 0) {
			newCli->setHostname(hostname);
		} else {
			newCli->setHostname(client_ip); // Use IP as fallback
		}
		//TODO: not throw an expection when a client cannot connect: it can't kill the server.
		if (fcntl(newCli->getFd(), F_SETFL, O_NONBLOCK) == -1) {
			close(newCli->getFd());
			throw Server::InitFailed(
				const_cast< const char * >(strerror(errno)));
		}
		cliEpollTemp.events = EPOLLIN;
		cliEpollTemp.data.fd = newCli->getFd();
		newCli->setCliEpoll(cliEpollTemp);

		if (epoll_ctl(epollFd_, EPOLL_CTL_ADD, newCli->getFd(),
					  newCli->getCliEpoll()) == -1) {
			close(newCli->getFd());
			throw Server::InitFailed(
				const_cast< const char * >(strerror(errno)));
		}

		clients_.insert(clientPair(newCli->getFd(), newCli));
		usedNicks_.push_back(newCli->getNick());
		std::stringstream ss;
		ss << "Client [" << newCli->getFd() << "] connected";
		// log(INFO, ss.str());
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}

bool Server::handleData(int fd)
{
	// log(INFO, "-----handleData-----");

	char tmpBuf[1024];
	memset(tmpBuf, 0, sizeof(tmpBuf));
	ssize_t bytes = recv(fd, tmpBuf, sizeof(tmpBuf) - 1, 0);
	std::string inputCli;
	inputCli.append(tmpBuf);

	Client *curCli = clients_.find(fd)->second;
	if (bytes <= 0)
		return (disconnectCli(fd));
	else {
		curCli->setBuffer(curCli->getBuffer().append(tmpBuf, bytes));
		processBuffer(curCli);
	}
	return (true);
}

void Server::processBuffer(Client *curCli)
{
	size_t pos;
	while ((pos = curCli->getBuffer().find('\n')) != std::string::npos) {
		if (!curCli->getBuffer().find("QUIT")) {
			std::cout << "Exit server" << std::endl;
			disconnectCli(curCli->getFd());
			return;
		}
		if (curCli->getBuffer().find("CAP LS") != std::string::npos ||
			curCli->getBuffer().find("NICK") != std::string::npos ||
			curCli->getBuffer().find("USER") != std::string::npos) {
			handleClientRegistration(curCli->getBuffer(), curCli);
			curCli->setBuffer("");
			return;
		} else {
			inputToken(curCli->getBuffer(), *curCli);
			curCli->setBuffer("");
			return;
		}
	}
}

Server &Server::GetServerInstance(int port, std::string password)
{
	static Server instance(port, password);
	return (instance);
}

bool Server::disconnectCli(int fd)
{
	clientMapIt it = clients_.find(fd);
	if (it != clients_.end()) {
		std::cout << "Client [" << fd << "] disconnected" << std::endl;
		delete it->second;
		clients_.erase(fd);
		close(fd);
		return true;
	}
	return false;
}

/* ************************************************************************** */
/*                               EXCEPTIONS                                   */
/* ************************************************************************** */

const char *Server::InitFailed::what() const throw()
{
	std::cerr << "irc: ";
	return errMessage;
}

Server::InitFailed::InitFailed(const char *err) : errMessage(err) {}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */
clientMap &Server::getAllCli()
{
	return (clients_);
}
channelMap &Server::getAllChan()
{
	return (channels_);
}