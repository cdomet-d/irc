/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:28:43 by aljulien          #+#    #+#             */
/*   Updated: 2025/02/20 18:44:50 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <vector>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <iostream>

class Client {
  public:
	/*                               ORTHODOX CLASS                           */
	Client(int servFd, int epollFd);
	~Client(void);
	/*                               EXCEPTIONS                                */
	class InitFailed : public std::exception {
		public:
			InitFailed(const char *err);
			const char *what() const throw();
		private:
			const char *errMessage;
	};
	/*                               METHODS                                  */

	/*                               GETTERS                                  */
	int getFd() const;
	std::string getName() const;
	std::string getNick() const;
	std::string getRealName() const;
	std::string getOpStatus() const;
	
	/*                               SETTERS                                  */
	void setOpStatus(bool isOp);
	void changeNick(const std::string &newNick);

  private:
	// user info
	std::string _name;
	std::string _realName;
	std::string _nick;
	std::string _pass;
	bool isOp;

	// socket infos
	struct sockaddr_in cliAddr;
	struct epoll_event cliEpoll;
	int cliFd;
	socklen_t len;
	std::string addrIP;

	// channels
	std::vector< int > joinedChans;

	/*                               METHODS                                  */
	// parsing
	bool isValidNick(const std::string &nick);
	
	// private constructors
	// Client(const Client &rhs) {}
	// Client(void) {}
	// Client &operator=(const Client &rhs) {}
};

#endif
