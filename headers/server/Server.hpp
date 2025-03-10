/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:50 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/10 16:36:08 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Channel.hpp"
#include "Client.hpp"
#include "typedef.hpp"
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

extern int gSign;
extern int gPort;
extern std::string gPassword;

class Client;

//TODO : add queue in case maxevent is returned, for handling too many events at once
class Server {

  public:
	/*                               ORTHODOX CLASS                           */
	static Server &GetServerInstance(int port, std::string password);
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
	void processBuffer(Client *currentCli);

	/*                               GETTERS                                  */
	clientMap &getAllCli();
	channelMap &getAllCha();

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

	clientMap _clients;
	channelMap _channels;
	std::vector< std::string > _usedNicks;

	// private constructor
	Server(void);
	Server(int port, std::string password);
};

/*                               PARSING                                  */
void inputToken(std::string inputCli, Client *curCli);

/*                               COMMAND                                  */
//NICK--USER
void handleClientRegistration(const std::string &input, Client *curCli);

//JOIN
Channel *createChannel(const std::string &channelName);
bool handleJoin(std::string params, Client *curCli);

//TOPIC
bool handleTopic(std::string params, Client *curCli);

//PRIVMSG
bool handlePrivsmg(std::string params, Client *currentCli);
//PART
bool handlePart(std::string params, Client *currentCli);
//MODE
bool handleMode(std::string params, Client *currentlCli);

/*                               DEBUG                                  */
void log(logLevel level, std::string message);
void log(logLevel level, std::string message, std::string additionalInfo);

#endif //SERVER_HPP
