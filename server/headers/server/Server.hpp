/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:50 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/23 17:52:48 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Channel.hpp"
#include "buffer_manip.hpp"
#include "typedef.hpp"
#include <arpa/inet.h>
#include <fstream>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>

class ObjectNotFound : public std::exception {
  public:
	ObjectNotFound(const char *err);
	const char *what() const throw();

  private:
	const char *errMessage;
};

extern int gSign;

class Client;

// TODO : add queue in case maxevent is returned, for handling too many events
// at once
class Server {

  public:
	/*                               ORTHODOX CLASS                           */
	static Server &GetServerInstance(int port, std::string password);
	~Server();

	/*                               EXCEPTIONS                                */
	class InitFailed : public std::exception {
	  public:
		InitFailed(const char *err);
		const char *what() const throw();

	  private:
		const char *errMessage;
	};

	/*                               METHODS                                  */
	bool servInit();
	bool servRun();
	Channel &findChan(const std::string &chanName);
	Client &findCli(int fd);
	void acceptClient();
	void addChan(Channel &curChan);
	void addNickToUsedNicks(const std::string &newNick, int fd);
	void checkChanInviteList(const Client &sender);
	void handleData(int fd);
	void removeChan(Channel &curChan);
	void removeCli(Client &curCli);
	void rmNickFromUsedNicks(const std::string &toRemove);

	/*                               GETTERS                                  */
	const channelMap &getAllChan() const;
	const clientMap &getAllCli() const;
	const nickMap &getUsedNick() const;
	const std::string &getPass() const;
	int getFdFromNick(const std::string &nick) const;

	/*                               MEMBERS                                  */
	std::ofstream logfile;

  private:
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
	Server operator=(const Server &rhs);
	Server();
	Server(const Server &rhs);
	Server(int port, std::string password);
};

#endif // SERVER_HPP
