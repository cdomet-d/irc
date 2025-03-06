/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:50 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/06 09:56:01 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Channel.hpp"
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
#define MAX_EVENTS 100

enum logLevel { INFO, ERROR, DEBUG };

extern int gSign;
extern int gPort;
extern std::string gPassword;

class Client;

//TODO : add queue in case maxevent is returned, for handling too many events at once
class Server {

  public:
	/*                               ORTHODOX CLASS                           */
	static Server &GetInstanceServer(int port, std::string password);
	~Server(void);

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
	
	/*                               GETTERS                                  */
	std::map< int, Client * > &getAllCli();
	std::map< std::string, Channel * > &getAllCha();

  private:
	/*                               METHODS                                  */
	bool disconnectClient(int fd);

	// attributes
	const int _port;
	const std::string _password;

	int _epollFd;
	int _servFd;
	struct epoll_event _events[MAX_EVENTS];
	struct epoll_event _servPoll;
	struct sockaddr_in _servAddress;

	std::map< int, Client * >			_client;
	std::map< std::string, Channel * >	_channels;
	std::vector< std::string >			_usedNicks;

	// private constructor
	Server(void);
	Server(int port, std::string password);
};

/*                               PARSING                                  */
std::vector< std::string > VectorSplit(std::string &s,
	const std::string &delimiter);
void	inputToken(std::string inputCli, int fd);

/*                               COMMAND                                  */
//NICK--USER
void	handleClientRegistration(const std::string& input, int fd);
//JOIN
Channel	*createChannel(const std::string& channelName);
bool	handleJoin(std::string params, int fd);
//TOPIC
bool handleTopic(std::string params, int fd);
//PRIVMSG
bool handlePrivsmg(std::string params, int fd);

/*                               DEBUG                                  */
void	log(logLevel level, std::string message);
void	log(logLevel level, std::string message, std::string additionalInfo);


#endif //SERVER_HPP
