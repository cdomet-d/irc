/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:50 by aljulien          #+#    #+#             */
/*   Updated: 2025/02/20 10:40:11 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#define MAX_EVENTS 100
extern int sign;
#include "Client.hpp"
#include <arpa/inet.h>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <netinet/in.h>
#include <poll.h>
#include <stdbool.h>
#include <string>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

class Client;

//TODO : see if we create map for channels
//TODO : add queue in case maxevent is returned, for handling too many events at once
//TODO : Encryption password ?
//TODO : check if we need to use IPv6 adresses or IPv4 is good enough ?
class Server {

  public:
	/*                               ORTHODOX CLASS                           */
	static Server *GetInstanceServer(int port, std::string password);
	~Server(void);

	/*                               METHODS                                  */
	bool servInit();
	bool servRun();
	bool acceptClient();

  private:
	static Server *_server;
	Server(int port, std::string password);

	const int _port;
	const std::string _password;
	std::map< int, Client & > _client;
	int _epollFd;
	int _servFd;
	struct epoll_event _servPoll;
	struct sockaddr_in _servAddress;
	struct epoll_event _events[MAX_EVENTS];

	Server(void);
};

#endif //SERVER_HPP
