/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:23:10 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/24 19:23:12 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
#define BOT_HPP

#include "Api.hpp"
#include "Message.hpp"
#include <arpa/inet.h>
#include <fstream>
#include <netinet/in.h>
#include <string>

class Bot {
  public:
	/*                               ORTHODOX CLASS                           */
	~Bot(void);

	/*                               METHODS                                  */
	static Bot &getInstance(int port, const std::string &pw,
							const std::string &servIp, char *envp[]);
	bool createChan();
	bool executeCmd();
	bool findLoginPos(const std::string &login);
	bool registration();
	bool registrationSequence();
	bool requestConnection();
	void clearMembers();
	ssize_t receive();

	/*                               GETTERS                                  */
	int getFd() const;
	bool getSignal() const;
	const stringVec &getMembers() const;
	const std::string getTarget() const;

	/*                               SETTERS                                  */
	void setSignal(const bool signum);
	void addClient(const std::string &nick);

	/*                               MEMBERS                                  */
	std::ofstream log_;

  private:
	/*                               MEMBERS                                  */

	// param e_param_;
	Msg msg_;
	stringVec members_;
	const std::string myChan_;
	Api api;

	int port_;
	int sockFd;
	bool gSign;
	std::string pw_;
	struct sockaddr_in serv_;

	/*                               ORTHODOX CLASS                           */
	Bot(void);
	Bot(int port, std::string pw, std::string servIp, char *envp[]);
	Bot(const Bot &rhs);
	Bot &operator=(const Bot &rhs);
};

#endif
