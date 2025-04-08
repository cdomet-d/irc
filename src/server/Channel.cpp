/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:43 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/07 17:36:06 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Server.hpp"

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */

Channel::Channel(std::string name)
	: inviteOnly_(false), isPassMatch_(false), topicRestrict_(true),
	  maxCli_(-1), name_(name), topic_("") {
	setModes();
}

Channel::~Channel(void) {
	// reply::INFO, "Channel deleted:", this->getName());
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */

void sendMessageChannel(clientMap allCliChannel, std::string message) {
	for (clientMapIt it = allCliChannel.begin(); it != allCliChannel.end();
		 ++it) {
		reply::send_(it->second->getFd(), message);
	}
}

bool Channel::addClientToChan(Channel *curChan, Client *sender) {
	curChan->addCli(ALLCLI, sender);
	sender->addOneChan(curChan->getName());
	if (curChan->getOpCli().empty())
		curChan->addCli(OPCLI, sender);
	if (curChan->getInvitCli().find(sender->getFd()) !=
		curChan->getInvitCli().end())
		curChan->removeCli(INVITECLI, sender->getFd());
	return (true);
}

void Channel::addCli(mapChan curMap, Client *sender) {
	switch (curMap) {
	case ALLCLI:
		cliInChan_.insert(clientPair(sender->getFd(), sender));
		break;
	case OPCLI:
		cliIsOperator_.insert(clientPair(sender->getFd(), sender));
		break;
	case INVITECLI:
		cliInvited_.insert(clientPair(sender->getFd(), sender));
	}
}

void Channel::removeCli(mapChan curMap, int fdCli) {
	switch (curMap) {
	case ALLCLI:
		cliInChan_.erase(fdCli);
		break;
	case OPCLI:
		cliIsOperator_.erase(fdCli);
		break;
	case INVITECLI:
		cliInvited_.erase(fdCli);
	}
}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */

std::string Channel::getName() const {
	return (name_);
}
std::string Channel::getTopic() const {
	return (topic_);
}
size_t Channel::getMaxCli() const {
	return (maxCli_);
}
bool Channel::getInviteOnly() const {
	return (inviteOnly_);
}
bool Channel::getIsPassMatch() const {
	return (isPassMatch_);
}
bool Channel::getTopicRestrict() const {
	return (topicRestrict_);
}
const clientMap &Channel::getCliInChan() const {
	return (cliInChan_);
}
const clientMap &Channel::getOpCli() const {
	return (cliIsOperator_);
}
const clientMap &Channel::getInvitCli() const {
	return (cliInvited_);
}
std::string Channel::getPassword() const {
	return (pass_);
}
std::string Channel::getModes() const {
	return (modes_);
}
/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */
void Channel::setName(std::string name) {
	name_ = name;
}
void Channel::setTopic(std::string topic) {
	topic_ = topic;
}
void Channel::setPassword(std::string password) {
	pass_ = password;
}
void Channel::setModes() {
	std::string modes = "+";

	if (getMaxCli() != 0)
		modes.append("l");
	if (getInviteOnly() == true)
		modes.append("i");
	if (getIsPassMatch() == true)
		modes.append("k");
	if (getTopicRestrict() == true)
		modes.append("t");
	modes_ = modes;
}
void Channel::setMaxCli(int maxCli) {
	maxCli_ = maxCli;
}
void Channel::setInviteOnly(bool inviteOnly) {
	inviteOnly_ = inviteOnly;
}
void Channel::setIsPassMatch(bool password) {
	isPassMatch_ = password;
}
void Channel::setTopicRestrict(bool topicRestrict) {
	topicRestrict_ = topicRestrict;
}
