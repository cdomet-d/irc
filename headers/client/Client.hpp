/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:28:43 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/11 11:22:21 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "typedef.hpp"
#include <fcntl.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

class Client {
  public:
	/*                               CONSTRUCTORS                             */
	Client(void);
	~Client(void);

	/*                               GETTERS                                  */
	int getFd() const;
	std::string getBuffer() const;
	std::string getHostname() const;
	std::string getIP() const;
	std::string getName() const;
	std::string getNick() const;
	std::string getPrefix() const;
	std::string getRealName() const;
	std::string getUsername() const;
	stringVec &getChans();
	struct epoll_event *getCliEpoll();

	/*                               SETTERS                                  */
	void setBuffer(std::string buffer);
	void setCliEpoll(struct epoll_event epoll);
	void setFd(int fd);
	void setHostname(std::string hostname);
	void setIP(std::string ip);
	void setNick(const std::string &newNick);
	void setPrefix();
	void setUsername(const std::string &username);

	/*                               MEMBERS                                  */
	struct sockaddr_in cliAddr_;

  private:
	/*                               MEMBERS                                  */
	// user info
	std::string hostname_;
	std::string ip_;
	std::string name_;
	std::string nick_;
	std::string pass_;
	std::string prefix_;
	std::string realName_;
	std::string username_;

	//attributes
	//int	registration;

	// socket infos
	int cliFd_;
	std::string buffer_;
	struct epoll_event cliEpoll_;

	// channels
	stringVec _RPL_JOINChans;

	/*                               METHODS                                  */
	// private constructors
	Client &operator=(const Client &rhs);
	Client(const Client &rhs);
};

#endif
