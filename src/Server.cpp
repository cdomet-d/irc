/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:39 by aljulien          #+#    #+#             */
/*   Updated: 2025/02/24 16:48:42 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <algorithm>
#include <cerrno>

// Server *Server::_server = NULL;

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */

Server::Server(int port, std::string password)
	: _port(port), _password(password) {}
// I think we can forbid server instantiation without parameters by putting the default constructor in private
Server::Server(void) : _port(0), _password("") {}

Server::~Server(void) {
	std::cout << "Calling destructor" << std::endl;
	for (std::map< int, Client * >::iterator it = _client.begin();
		 it != _client.end(); ++it) {
		close(it->first);
		delete it->second;
	}
	close(_epollFd);
	close(_servFd);
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */

//TODO : need to determine is false means the function work or something went wrong
// coralie: false means something went wrong IMO
bool Server::servInit() {
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

bool Server::servRun() {
	int nbFds;

	std::cout << "Server listening on port " << _port
			  << " | IP adress: " << inet_ntoa(_servAddress.sin_addr)
			  << std::endl;
	while (sign == false) {
		nbFds = epoll_wait(_epollFd, _events, MAX_EVENTS, -1);
		if (nbFds == -1 && sign == false)
			return (false);
		for (int i = 0; i < nbFds; i++) {
			if (_events[i].data.fd == _servFd)
				acceptClient();
 			else if (handleData(_events[i].data.fd) == false)
				return true;
		}
	}
	return (true);
}

//TODO : needs to be rework to get the IP address of each client
void Server::acceptClient() {
	try {
		Client *newCli = new Client();
		struct epoll_event cliEpollTemp;
		newCli->setFd(accept(_servFd, NULL, 0));
		
		if (newCli->getFd() == -1)
			throw Server::InitFailed(const_cast< const char * >(strerror(errno)));
		
		if (fcntl(newCli->getFd(), F_SETFL, O_NONBLOCK) == -1) {
			close(newCli->getFd());
			throw Server::InitFailed(const_cast< const char * >(strerror(errno)));
		}
		
		cliEpollTemp.events = EPOLLIN;
		cliEpollTemp.data.fd = newCli->getFd();
		newCli->setCliEpoll(cliEpollTemp);
		
		if (epoll_ctl(_epollFd, EPOLL_CTL_ADD, newCli->getFd(), newCli->getCliEpoll()) == -1) {
			close(newCli->getFd());
			throw Server::InitFailed(const_cast< const char * >(strerror(errno)));
		}
		
		_client.insert(std::pair< int, Client * >(newCli->getFd(), newCli));
		_usedNicks.push_back(newCli->getNick());
		std::cout << "Client [" << newCli->getFd() << "] connected " << std::endl;
	} catch (std::exception &e) { std::cerr << e.what() << std::endl; }

}

bool Server::handleData(int fd) {
	// TODO: Limit message size
	// Most IRC servers limit messages to 512 bytes in length,
	//including the trailing CR-LF characters. Implementations which include
	//message tags need to allow additional bytes for the tags section of a
	//message; clients must allow 8191 additional bytes and servers must allow
	// 4096 additional bytes
	char bufTemp[1024];
	memset(bufTemp, 0, sizeof(bufTemp));
	ssize_t bytes = recv(fd, bufTemp, sizeof(bufTemp) - 1, 0);
	std::string buffer = bufTemp;

	if (bytes <= 0)
		return (disconnectClient(fd));
	else {

		if (strncmp(buffer.c_str(), "NICK", 4) == 0) {
			std::string nick;
			buffer.erase(0, 5);
			for (int i = 0; buffer.c_str()[i] != '\n'; i++)
				nick.push_back(buffer.c_str()[i]);
			std::map<int, Client *>::iterator it = _client.find(fd);
			it->second->setNick(nick);
		}
		if (buffer.find("USER") != buffer.npos) {
			size_t n = buffer.find("USER");
			buffer.erase(n, n + 4);
			std::string user;
			for (int i = 0; buffer.c_str()[i] != '\n'; i++)
				user.push_back(buffer.c_str()[i]);
			std::map<int, Client *>::iterator it = _client.find(fd);
			it->second->setUsername(user);
		}
		//TODO : the server sends the client this formatted message to let him know he joined a channel 
		//:Alice!alice@example.com JOIN #example
		if (strncmp(bufTemp, "JOIN #", 5) == 0) {
			std::map<int, Client *>::iterator it = _client.find(fd);
			std::string message = ":" + it->second->getNick() + "!" +it->second->getUsername() + "@" + "0.0.0.0.com JOIN #test";
		
			send(fd, message.c_str(), strlen(message.c_str()), 0);
			
			std::cout << "Client <" << fd << "> joined " << (bufTemp + 6) << std::endl;
		}

		if (strncmp(bufTemp, "QUIT", 4) == 0) {
			std::cout << "Exit server" << std::endl;
			return false;
		}
		return (true);
	}
}

Server &Server::GetInstanceServer(int port, std::string password) {
	static Server instance(port, password);
	return (instance);
}

bool Server::disconnectClient(int fd) {
	std::map< int, Client * >::iterator it = _client.find(fd);
	if (it != _client.end()) {
		std::cout << "Client [" << fd << "] disconnected" << std::endl;
		delete it->second;
		_client.erase(fd);
		close(fd);
		return true;
	}
	return false;
}

/* ************************************************************************** */
/*                               EXCEPTIONS                                   */
/* ************************************************************************** */

const char *Server::InitFailed::what() const throw() {
	std::cerr << "irc: ";
	return errMessage;
}

Server::InitFailed::InitFailed(const char *err) : errMessage(err) {}
