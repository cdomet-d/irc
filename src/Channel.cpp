/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:43 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/10 10:21:25 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Server.hpp"

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */

Channel::Channel(std::string name)
	: _name(name), _topic(""), _maxCli(0), _inviteOnly(false),
	  _isPassword(false), _isLimitCli(false)
{
}

Channel::~Channel(void)
{
	log(INFO, "Channel deleted:", this->getName());
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */

bool Channel::addClientChannel(Channel *currentChannel, Client *currentCli)
{
	//log(DEBUG, "-----addClientChannel-----");

	std::map< int, Client * > &clients = currentChannel->getCliInChannel();
	for (std::map< int, Client * >::iterator it = clients.begin();
		 it != clients.end(); ++it)
		if (currentCli == it->second) {
			log(INFO, "Client already in channel");
			return (false);
		}
	if (currentChannel->getCliInChannel().empty())
		currentChannel->getOpCli().insert(
			std::pair< int, Client * >(currentCli->getFd(), currentCli));
	currentChannel->getCliInChannel().insert(
		std::pair< int, Client * >(currentCli->getFd(), currentCli));
	currentCli->getJoinedChans().push_back(currentChannel->getName());

	for (std::map< int, Client * >::iterator itCli =
			currentChannel->getCliInChannel().begin();
		itCli != currentChannel->getCliInChannel().end(); ++itCli) {
		sendReply(itCli->second->getFd(),
			  JOINED(currentCli->getNick(), currentChannel->getName()));
	}
	if (currentChannel->getTopic().empty() == true)
		sendReply(currentCli->getFd(), RPL_NOTOPIC(currentCli->getNick(),
												   currentChannel->getName()));
	else
		sendReply(currentCli->getFd(),
				  RPL_TOPIC(currentCli->getNick(), currentChannel->getName(),
							currentChannel->getTopic()));
	return (true);
}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */

std::string Channel::getName() const
{
	return (_name);
}
std::string Channel::getTopic() const
{
	return (_topic);
}
int Channel::getMaxCli() const
{
	return (_maxCli);
}
bool Channel::getInviteOnly() const
{
	return (_inviteOnly);
}
bool Channel::getIsPassword() const
{
	return (_isPassword);
}
bool Channel::getLimitCli() const
{
	return (_isLimitCli);
}
std::map< int, Client * > &Channel::getCliInChannel()
{
	return (_cliInChannel);
}
std::map< int, Client * > &Channel::getBannedCli()
{
	return (_bannedCli);
}
std::map< int, Client * > &Channel::getOpCli()
{
	return (_opCli);
}
std::string Channel::getPassword() const
{
	return (_password);
}
/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */
void Channel::setName(std::string name)
{
	_name = name;
}
void Channel::setTopic(std::string topic)
{
	_topic = topic;
}
void Channel::setPassword(std::string password)
{
	_password = password;
}