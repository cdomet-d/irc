/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:38 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/07 13:23:00 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "reply.h"
#include "typedef.hpp"
#include "Client.hpp"
#include "reply.h"
#include <iostream>
#include <map>
#include <string>

class Client;

class Channel {
  public:
	/*                               ORTHODOX CLASS                           */
	Channel(std::string name);
	~Channel(void);

	/*                               METHODS                                  */
	bool addClientChannel(Channel *currentChannel, Client *currentCli);

	/*                               GETTERS                                  */
	std::string	getName() const;
	std::string	getTopic() const;
	int			getMaxCli() const;
	bool		getInviteOnly() const;
	bool		getIsPassword() const;
	bool		getLimitCli() const;
	clientMap	&getCliInChannel();
	clientMap	&getBannedCli();
	clientMap	&getOpCli();
	
	/*                               SETTERS                                  */
	void setName(std::string name);
	void setTopic(std::string topic);
	void setPassword(std::string password);

  private:
	std::string _name;
	std::string _topic;
	std::string _password;

	int _maxCli;
	bool _inviteOnly;
	bool _isPassword;
	bool _isLimitCli;

	clientMap _cliInChannel;
	clientMap _bannedCli;
	clientMap _opCli;
};

#endif
