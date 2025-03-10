/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:43 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/10 11:12:15 by aljulien         ###   ########.fr       */
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

bool Channel::addClientChannel(Channel *curChan, Client *currentCli) {
	//log(DEBUG, "-----addClientChannel-----");

	static Server &server = Server::GetInstanceServer(gPort, gPassword);

	clientMapIt whatCli = server.getAllCli().find(currentCli->getFd());
	clientMap &clients = curChan->getCliInChannel();
	for (clientMapIt it = clients.begin(); it != clients.end(); ++it)
		if (whatCli->second == it->second) {
			log(INFO, "Client already in channel");
			return (false);
		}
	if (curChan->getCliInChannel().empty())
		curChan->getOpCli().insert(clientPair(currentCli->getFd(), whatCli->second));
	curChan->getCliInChannel().insert(clientPair(currentCli->getFd(), whatCli->second));
	whatCli->second->getJoinedChans().push_back(curChan->getName());

	sendReply(currentCli->getFd(), JOINED(whatCli->second->getNick(), curChan->getName()));
	if (curChan->getTopic().empty() == true)
		sendReply(currentCli->getFd(),
				  RPL_NOTOPIC(whatCli->second->getNick(), curChan->getName()));
	else
		sendReply(currentCli->getFd(), RPL_TOPIC(whatCli->second->getNick(), curChan->getName(),
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
bool Channel::getLimitCli() const
{
	return (_isLimitCli);
}
clientMap &Channel::getCliInChannel() {
	return (_cliInChannel);
}
clientMap &Channel::getBannedCli() {
	return (_bannedCli);
}
clientMap &Channel::getOpCli() {
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