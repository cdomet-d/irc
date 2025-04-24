/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:28:43 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/24 10:36:45 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Message.hpp"
#include "UserInfo.hpp"
#include <fcntl.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

class Client {
  public:
	/*                               CONSTRUCTORS                             */
	Client();
	~Client();

	/*                               GETTERS                                  */
	int getFd() const;
	const stringVec &getJoinedChans() const;
	struct epoll_event *getCliEpoll();

	/*                               SETTERS                                  */
	void setCliEpoll(struct epoll_event epoll);
	void setFd(int fd);

	/*                               MEMBERS                                  */
	void removeOneChan(std::string chanName);
	void addOneChan(std::string chanName);

	Message mess;
	struct sockaddr_in cliAddr_;
	UserInfo cliInfo;

  private:
	/*                               MEMBERS                                  */
	// sockets
	int cliFd_;
	struct epoll_event cliEpoll_;

	// channels
	stringVec joinedChans_;

	// private constructors
	Client &operator=(const Client &rhs);
	Client(const Client &rhs);
};

#endif