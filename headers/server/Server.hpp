/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:50 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/28 16:15:00 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "buffer_manip.hpp"
#include "Channel.hpp"
#include "typedef.hpp"
#include <arpa/inet.h>
#include <fstream>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>

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
	void addChan(Channel *curChan);
	void addNickToUsedNicks(const std::string &newNick, int fd);
	void removeNickFromUsedNicks(const std::string &toRemove);
	void removeChan(Channel *curChan);
	void removeCli(Client *curCli);

	/*                               GETTERS                                  */
	const nickMap &getUsedNick() const;
	int getFdFromNick(const std::string &nick) const;
	const std::string getPass() const;

	/*                               MEMBERS                                  */
	std::ofstream logfile;


	const clientMap &getAllCli() const;
	const channelMap &getAllChan() const;

  private:
	/*                               METHODS                                  */

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

#endif //SERVER_HPP
