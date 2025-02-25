/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:50 by aljulien          #+#    #+#             */
/*   Updated: 2025/02/25 16:51:11 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Client.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <map>
#include <netinet/in.h>
#include <poll.h>
#include <string>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

enum logLevel { INFO, ERROR, DEBUG };

#define MAX_EVENTS 100
extern int gSign;
extern int gPort;
extern std::string gPassword;

class Client;

//TODO : Create log function
//TODO : see if we create map for channels
//TODO : add queue in case maxevent is returned, for handling too many events at once
//TODO : Encryption password ?
//TODO : check if we need to use IPv6 adresses or IPv4 is good enough ?
class Server {

  public:
	/*                               ORTHODOX CLASS                           */
	static Server &GetInstanceServer(int port, std::string password);
	~Server(void);

	std::map< int, Client * > _client;

	/*                               EXCEPTIONS                                */
	class InitFailed : public std::exception {
	  public:
		InitFailed(const char *err);
		const char *what() const throw();

	  private:
		const char *errMessage;
	};

	/*                               METHODS                                  */
	bool handleData(int fd);
	bool servInit();
	bool servRun();
	void acceptClient();

  private:
	/*                               METHODS                                  */
	bool disconnectClient(int fd);
	// constructor
	Server(int port, std::string password);

	// attributes
	// std::map< int, Channel * > _channel;
	const int _port;
	const std::string _password;
	int _epollFd;
	int _servFd;
	std::vector< std::string > _usedNicks;
	struct epoll_event _events[MAX_EVENTS];
	struct epoll_event _servPoll;
	struct sockaddr_in _servAddress;

	// private constructor
	Server(void);
};

void log(logLevel level, std::string message);
void log(logLevel level, std::string message, std::string additionalInfo);
std::vector< std::string > VectorSplit(std::string &s,
									   const std::string &delimiter);
bool handleNick(std::string buffer, int fd);
std::string findNick(std::string &buffer);
bool handleUsername(std::string buffer, int fd);
std::string findUsername(std::string &buffer);

#endif //SERVER_HPP
