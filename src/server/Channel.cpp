/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:43 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/10 16:42:17 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Server.hpp"

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */

Channel::Channel(std::string name)
	: _name(name), _topic(""), _maxCli(0), _inviteOnly(false),
	  _isPassword(false), topicRestrict_(false)
{
	setModes();
}

Channel::~Channel(void)
{
	log(INFO, "Channel deleted:", this->getName());
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */

bool Channel::addClientChannel(Channel *curChan, Client *curCli)
{
	//log(DEBUG, "-----addClientChannel-----");

	clientMap &clients = curChan->getCliInChan();
	for (clientMapIt it = clients.begin(); it != clients.end(); ++it)
		if (curCli == it->second) {
			log(INFO, "Client already in channel");
			return (false);
		}
	if (curChan->getCliInChan().empty())
		curChan->getOpCli().insert(clientPair(curCli->getFd(), curCli));
	curChan->getCliInChan().insert(clientPair(curCli->getFd(), curCli));
	curCli->getJoinedChans().push_back(curChan->getName());

	sendReply(curCli->getFd(), JOINED(curCli->getNick(), curChan->getName()));
	if (curChan->getTopic().empty() == true)
		sendReply(curCli->getFd(),
				  RPL_NOTOPIC(curCli->getNick(), curChan->getName()));
	else
		sendReply(curCli->getFd(),
				  RPL_TOPIC(curCli->getNick(), curChan->getName(),
							curChan->getTopic()));
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
bool Channel::getTopicRestrict() const 
{
	return (topicRestrict_);
}
clientMap &Channel::getCliInChannel() {
	return (_cliInChannel);
}
clientMap &Channel::getOpCli() {
	return (_opCli);
}
std::string Channel::getPassword() const
{
	return (_password);
}
std::string Channel::getModes() const
{
	return (modes_);
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
void Channel::setModes()
{
	std::string modes = "+";

	if (getMaxCli() != 0)
		modes.append("l");
	if (getInviteOnly() == true)
		modes.append("i");
	if (getIsPassword() == true)
		modes.append("k");
	if (getTopicRestrict() == true)
		modes.append("t");
	modes_ = modes;
}
void Channel::setMaxCli(int maxCli) 
{
	_maxCli = maxCli;
}
void Channel::setInviteOnly(bool inviteOnly)
{
	_inviteOnly = inviteOnly;
}
void Channel::setIspassword(bool isPassword)
{
	_isPassword = isPassword;	
}
void Channel::setTopicRestrict(bool topicRestrict)
{
	topicRestrict_ = topicRestrict;
}