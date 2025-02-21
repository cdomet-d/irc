/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:50 by aljulien          #+#    #+#             */
/*   Updated: 2025/02/21 13:56:18 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#define MAX_EVENTS 100
extern int sign;

#include "Client.hpp"
#include <arpa/inet.h>
#include <iostream>
#include <map>
#include <netinet/in.h>
#include <poll.h>
#include <string>

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
	void acceptClient();

  private:
	static Server *_server;
	Server(int port, std::string password);

	// std::map< int, Channel & > _channel;
	const int _port;
	const std::string _password;
	int _epollFd;
	int _servFd;
	std::map< int, Client * > _client;
	std::vector< std::string > _usedNicks;
	struct epoll_event _events[MAX_EVENTS];
	struct epoll_event _servPoll;
	struct sockaddr_in _servAddress;

	Server(void);
};

#endif //SERVER_HPP
