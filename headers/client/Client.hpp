/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:28:43 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/07 13:21:39 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <fcntl.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

class	Client
{
	private:
		//attributes
		int	registration;
	public:
		//constructors & destructor
		Client(void);
		~Client(void);

	/*                               METHODS                                  */

	/*                               GETTERS                                  */
	int getFd() const;
	std::string getName() const;
	std::string getNick() const;
	std::string getUsername() const;
	std::string getRealName() const;
	std::string getHostname() const;
	struct epoll_event *getCliEpoll();
	std::string getIP() const;
	std::string getPrefix() const;
	std::string getBuffer() const;
	std::vector< std::string > &getJoinedChans();

	/*                               SETTERS                                  */
	void setNick(const std::string &newNick);
	void setUsername(const std::string &username);
	void setFd(int fd);
	void setCliEpoll(struct epoll_event epoll);
	void setIP(std::string ip);
	void setHostname(std::string hostname);
	void setPrefix();
	void setBuffer(std::string buffer);

	struct sockaddr_in _cliAddress;

  private:
	// user info
	std::string _name;
	std::string _nick;
	std::string _username;
	std::string _pass;
	std::string _realName;
	std::string _IP;
	std::string _hostname;
	std::string _prefix;

	// socket infos
	struct epoll_event _cliEpoll;
	int _cliFd;
	std::string _buffer;

	// channels
	std::vector< std::string > _joinedChans;

	/*                               METHODS                                  */
	// private constructors
	Client(const Client &rhs);
	Client &operator=(const Client &rhs);
};

#endif
