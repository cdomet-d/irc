/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:38 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/10 10:24:55 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "typedef.hpp"
#include "Client.hpp"
#include "Reply.hpp"
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
	bool addClientChannel(Channel *curChan, Client *curCli);

	/*                               GETTERS                                  */
	bool		getInviteOnly() const;
	bool		getIsPassword() const;
	bool		getLimitCli() const;
	clientMap	&getBannedCli();
	clientMap	&getCliInChan();
	clientMap	&getOpCli();
	int			getMaxCli() const;
	std::string	getPassword() const;
	std::string	getName() const;
	std::string	getTopic() const;
	
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
