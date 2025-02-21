/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:28:43 by aljulien          #+#    #+#             */
/*   Updated: 2025/02/21 14:31:14 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

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
	bool getOpStatus() const;
	int getFd() const;
	std::string getName() const;
	std::string getNick() const;
	std::string getRealName() const;

	/*                               SETTERS                                  */
	void setOpStatus(bool isOp);
	void setNick(const std::string &newNick);

  private:
	// user info
	bool _isOp;
	std::string _name;
	std::string _nick;
	std::string _pass;
	std::string _realName;

	// socket infos
	struct epoll_event cliEpoll;
	int cliFd;

	// channels
	std::vector< int > joinedChans;

	/*                               METHODS                                  */
	// private constructors
	Client(const Client &rhs);
	Client(void);
	Client &operator=(const Client &rhs);
};

#endif
