/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:43 by aljulien          #+#    #+#             */
/*   Updated: 2025/02/28 15:07:05 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Channel.hpp"

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */

Channel::Channel(std::string name)
	: _name(name), _topic(""), _maxCli(0), _inviteOnly(false), _isPassword(false), _isLimitCli(false)
{}

Channel::~Channel(void) {
	log(INFO, "Channel deleted:", this->getName());
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */

bool Channel::addClientChannel(Channel *currentChannel, int fd)
{
	//log(DEBUG, "-----addClientChannel-----");

	static Server &server = Server::GetInstanceServer(gPort, gPassword);

	std::map< int, Client * >::iterator whatCli = server.getAllCli().find(fd);
	std::map< int, Client * >& clients = currentChannel->getAllCli();
	for (std::map< int, Client * >::iterator it = clients.begin(); it != clients.end(); ++it)
		if (whatCli->second == it->second)
			log(INFO, "Client already in channel");
	if (currentChannel->getAllCli().empty())
		currentChannel->getOpCli().insert(std::pair< int, Client * >(fd, whatCli->second));	
	currentChannel->getAllCli().insert(std::pair< int, Client * >(fd, whatCli->second));

	sendReply(fd, JOINED(whatCli->second->getNick(), currentChannel->getName()));
	sendReply(fd, RPL_TOPIC(whatCli->second->getNick(), currentChannel->getName(), "topic"));

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
std::map< int, Client * > &Channel::getAllCli() {
	return (_allCli);
}
std::map< int, Client * > &Channel::getBannedCli() {
	return (_bannedCli);
}
std::map< int, Client * > &Channel::getOpCli() {
	return (_opCli);
}

/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */
void Channel::setName(std::string name)
{
	_name = name;
}