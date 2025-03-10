/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:43 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/10 10:17:07 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Server.hpp"

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */

Channel::Channel(std::string name)
	: _name(name), _topic(""), _maxCli(0), _inviteOnly(false),
	  _isPassword(false), _isLimitCli(false) {}

Channel::~Channel(void) {
	log(INFO, "Channel deleted:", this->getName());
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */

bool Channel::addClientChannel(Channel *curChan, Client *curCli) {
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

std::string Channel::getName() const {
	return (_name);
}
std::string Channel::getTopic() const {
	return (_topic);
}
int Channel::getMaxCli() const {
	return (_maxCli);
}
bool Channel::getInviteOnly() const {
	return (_inviteOnly);
}
bool Channel::getIsPassword() const {
	return (_isPassword);
}
bool Channel::getLimitCli() const {
	return (_isLimitCli);
}
clientMap &Channel::getCliInChan() {
	return (_cliInChannel);
}
clientMap &Channel::getBannedCli() {
	return (_bannedCli);
}
clientMap &Channel::getOpCli() {
	return (_opCli);
}
std::string Channel::getPassword() const {
	return (_password);
}
/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */
void Channel::setName(std::string name) {
	_name = name;
}
void Channel::setTopic(std::string topic) {
	_topic = topic;
}
void Channel::setPassword(std::string password) {
	_password = password;
}