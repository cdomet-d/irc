/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:43 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/06 14:05:02 by cdomet-d         ###   ########.fr       */
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

bool Channel::addClientChannel(Channel *curChan, int fd) {
	//log(DEBUG, "-----addClientChannel-----");

	static Server &server = Server::GetInstanceServer(gPort, gPassword);

	clientMapIt whatCli = server.getAllCli().find(fd);
	clientMap &clients = curChan->getCliInChannel();
	for (clientMapIt it = clients.begin(); it != clients.end(); ++it)
		if (whatCli->second == it->second) {
			log(INFO, "Client already in channel");
			return (false);
		}
	if (curChan->getCliInChannel().empty())
		curChan->getOpCli().insert(clientPair(fd, whatCli->second));
	curChan->getCliInChannel().insert(clientPair(fd, whatCli->second));
	whatCli->second->getJoinedChans().push_back(curChan->getName());

	sendReply(fd, JOINED(whatCli->second->getNick(), curChan->getName()));
	if (curChan->getTopic().empty() == true)
		sendReply(fd,
				  RPL_NOTOPIC(whatCli->second->getNick(), curChan->getName()));
	else
		sendReply(fd, RPL_TOPIC(whatCli->second->getNick(), curChan->getName(),
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
clientMap &Channel::getCliInChannel() {
	return (_cliInChannel);
}
clientMap &Channel::getBannedCli() {
	return (_bannedCli);
}
clientMap &Channel::getOpCli() {
	return (_opCli);
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