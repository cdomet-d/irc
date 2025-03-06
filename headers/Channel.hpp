/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:38 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/06 17:38:00 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "reply.h"
#include "Client.hpp"
#include <map>
#include <iostream>
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
	std::string getPassword() const;
	int			getMaxCli() const;
	bool		getInviteOnly() const;
	bool		getIsPassword() const;
	bool		getLimitCli() const;
	std::map< int, Client * >	&getCliInChannel();
	std::map< int, Client * >	&getBannedCli();
	std::map< int, Client * >	&getOpCli();
	
	/*                               SETTERS                                  */
	void setName(std::string name);
	void setTopic(std::string topic);
	void setPassword(std::string password);


  private:
	std::string _name;
	std::string _topic;
	std::string _password;
	
	int		_maxCli;
	bool	_inviteOnly;
	bool	_isPassword;
	bool	_isLimitCli;

	std::map< int, Client * > _cliInChannel;
	std::map< int, Client * > _bannedCli;
	std::map< int, Client * > _opCli;
};

#endif
