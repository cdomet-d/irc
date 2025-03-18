/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:50 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/18 18:00:18 by cdomet-d         ###   ########.fr       */
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

// enum logLevel { INFO, ERROR, DEBUG };

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

	/*                               GETTERS                                  */
	clientMap &getAllCli();
	channelMap &getAllChan();
	const nickMap &getUsedNick() const;
	int getFdFromNick(const std::string &nick) const;

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
	nickMap usedNicks_;

	// private constructor
	Server(void);
	Server(int port, std::string password);
};


/*                               COMMAND                                  */
//NICK--USER
void handleClientRegistration(const std::string &input, Client *curCli);

//JOIN
bool handleJoin(std::string params, Client *curCli);
Channel *createChan(const std::string &chanName);
//TOPIC
bool handleTopic(std::string params, Client *curCli);
//PRIVMSG
bool handlePrivsmg(std::string params, Client *curCli);
//PART
bool handlePart(std::string params, Client *curCli);
//MODE
bool handleMode(std::string params, Client *currentlCli);

/*                               DEBUG                                  */
// void logger(logLevel level, std::string message);
// void logger(logLevel level, std::string message, std::string additionalInfo);

#endif //SERVER_HPP
