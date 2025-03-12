/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:28:43 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/12 14:26:50 by cdomet-d         ###   ########.fr       */
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
	stringVec &getJoinedChans();
	stringVec getCmdParam();
	struct epoll_event *getCliEpoll();

	/*                               SETTERS                                  */
	void setBuffer(std::string buffer);
	void setCmdParam(const stringVec &splitBuffer);
	void setTrailingParam(const std::string &trail);
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
	struct epoll_event cliEpoll_;

	// message transmission
	std::string buffer_;
	stringVec cmdParam_;

	// channels
	stringVec joinedChans_;

	/*                               METHODS                                  */
	// private constructors
	Client &operator=(const Client &rhs);
	Client(const Client &rhs);
};

#endif
