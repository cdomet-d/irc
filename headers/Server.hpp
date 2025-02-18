/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:50 by aljulien          #+#    #+#             */
/*   Updated: 2025/02/18 17:14:04 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#define MAX_EVENTS 100

#include "Client.hpp"
#include <iostream>
#include <map>
#include <netinet/in.h>
#include <stdbool.h>
#include <string>
#include <sys/epoll.h>

class Client;

//TODO : see if we create map for channels
//TODO : add queue in case maxevent is returned, for handling too many events at once
//TODO : Encryption password ?
//TODO : check if we need to use IPv6 adresses or IPv4 is good enough ?
class Server {

  public:
	/*                               ORTHODOX CLASS                           */
	Server(void);
	Server(const Server &rhs);
	~Server(void);
	Server &operator=(const Server &rhs);

	/*                               METHODS                                  */
	bool servInit();
	bool servRun();
	bool acceptClient();

  private:
	const std::string _password;
	std::map< int, Client & > _client;
	const int _port;
	int _epollfd;
	int _servFd;
	struct epoll_event _servPoll;
	struct sockaddr_in _servAddress;
};

#endif //SERVER_HPP
