/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:38 by aljulien          #+#    #+#             */
/*   Updated: 2025/02/28 14:40:38 by aljulien         ###   ########.fr       */
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
	bool addClientChannel(Channel *currentChannel, int fd);
	
	/*                               GETTERS                                  */
	std::string	getName() const;
	std::string	getTopic() const;
	int			getMaxCli() const;
	bool		getInviteOnly() const;
	bool		getIsPassword() const;
	bool		getLimitCli() const;
	std::map< int, Client * >	&getAllCli();
	std::map< int, Client * >	&getBannedCli();
	std::map< int, Client * >	&getOpCli();
	
	/*                               SETTERS                                  */
	void setName(std::string name);

	private:
	std::string _name;
	std::string _topic;
	
	int			_maxCli;
	bool _inviteOnly;
	bool _isPassword;
	bool _isLimitCli;
	std::map< int, Client * > _allCli;
	std::map< int, Client * > _bannedCli;
	std::map< int, Client * > _opCli;
};

#endif
