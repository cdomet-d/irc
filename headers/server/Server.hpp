/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:50 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/20 11:11:07 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Channel.hpp"
#include "MessageValidator.hpp"
#include "typedef.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <fstream>
#include <netinet/in.h>
#include <poll.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

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
	void addChan(Channel *curChan);
	void removeChan(Channel *curChan);

	/*                               GETTERS                                  */
	const clientMap &getAllCli() const;
	const channelMap &getAllChan() const;

	/*                               GETTERS                                  */
	const nickMap &getUsedNick() const;
	int getFdFromNick(const std::string &nick) const;
	const std::string getPass() const;

	/*                               MEMBERS                                  */
	std::ofstream logfile;

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

//PRIVMSG
bool privmsgExec(std::string params, Client *curCli);
//WHO
bool whoExec(std::string params, Client *curCli);
//PASS
bool passExec(std::string params, Client *curCli);

#endif //SERVER_HPP
