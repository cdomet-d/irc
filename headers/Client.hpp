/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:28:43 by aljulien          #+#    #+#             */
/*   Updated: 2025/02/24 12:29:45 by aljulien         ###   ########.fr       */
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
	Client(void);
	~Client(void);

	/*                               METHODS                                  */

	/*                               GETTERS                                  */
	bool getOpStatus() const;
	int getFd() const;
	std::string getName() const;
	std::string getNick() const;
	std::string getRealName() const;
	struct epoll_event getCliEpoll() const;

	/*                               SETTERS                                  */
	void setOpStatus(bool isOp);
	void setNick(const std::string &newNick);
	void setFd(int fd);
	void setCliEpoll(struct epoll_event epoll);

  private:
	// user info
	bool _isOp;
	std::string _name;
	std::string _nick;
	std::string _pass;
	std::string _realName;

	// socket infos
	struct epoll_event _cliEpoll;
	int _cliFd;

	// channels
	std::vector< int > joinedChans;

	/*                               METHODS                                  */
	// private constructors
	Client(const Client &rhs);
	Client &operator=(const Client &rhs);
};

#endif
