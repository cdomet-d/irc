/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:50 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/19 15:45:01 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Channel.hpp"
#include "MessageValidator.hpp"
#include "typedef.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <netinet/in.h>
#include <poll.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

enum logEnum { INFO, ERROR, DEBUG };

extern int gSign;

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
	void processBuffer(Client *curCli);
	void addCli(int fdCli);
	void removeCli(int fdCli);
	void addChan(std::string nameChan);
	void removeChan(std::string nameChan);

	/*                               GETTERS                                  */
	clientMap &getAllCli();
	channelMap &getAllChan();
	std::string getPass() const;

  private:
	/*                               METHODS                                  */
	bool disconnectCli(int fd);

	// attributes
	const int port_;
	const std::string pass_;

	int epollFd_;
	int servFd_;
	struct epoll_event events_[MAX_EVENTS];
	struct epoll_event servPoll_;
	struct sockaddr_in servAddr_;

	clientMap clients_;
	channelMap channels_;
	stringVec usedNicks_;

	// private constructor
	Server(void);
	Server(int port, std::string password);
};

/*                               COMMAND                                  */
//NICK--USER
void handleClientRegistration(const std::string &input, Client *curCli);

//PRIVMSG
bool handlePrivsmg(std::string params, Client *curCli);
//WHO
bool handleWho(std::string params, Client *curCli);
//PASS
bool handlePass(std::string params, Client *curCli);

/*                               DEBUG                                  */
void logLevel(logEnum level, std::string message);
void logLevel(logEnum level, std::string message, std::string additionalInfo);

#endif //SERVER_HPP
