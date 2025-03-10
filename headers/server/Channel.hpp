/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:38 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/10 16:34:32 by cdomet-d         ###   ########.fr       */
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
	std::string getPassword() const;
	std::string getModes() const;

	int			getMaxCli() const;
	bool		getInviteOnly() const;
	bool		getIsPassword() const;
	bool		getTopicRestrict() const;
	clientMap	&getCliInChannel();
	clientMap	&getOpCli();
	
	/*                               SETTERS                                  */
	void setName(std::string name);
	void setTopic(std::string topic);
	void setPassword(std::string password);
	void setModes();
	
	void setMaxCli(int maxCli);
	void setInviteOnly(bool inviteOnly);
	void setIspassword(bool isPassword);
	void setTopicRestrict(bool topicRestrict); 

  private:
	std::string _name;
	std::string _topic;
	std::string _password;
	std::string modes_;

	int _maxCli;
	bool _inviteOnly;
	bool _isPassword;
	bool topicRestrict_;

	clientMap _cliInChannel;
	clientMap _opCli;
};

#endif
