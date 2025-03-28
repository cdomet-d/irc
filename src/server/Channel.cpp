/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:43 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/28 09:04:23 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Server.hpp"

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */

Channel::Channel(std::string name)
	: inviteOnly_(true), isPassMatch_(false), topicRestrict_(true), maxCli_(-1),
	  name_(name), topic_("") {
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

	sender->getJoinedChans().push_back(curChan->getName());

	for (clientMapIt itCli = curChan->getCliInChan().begin();
		 itCli != curChan->getCliInChan().end(); ++itCli) {
		reply::send_(
			itCli->second->getFd(),
			RPL_JOIN(sender->cliInfo.getPrefix(), curChan->getName()));
	}
	if (curChan->getTopic().empty() == true)
		reply::send_(sender->getFd(), RPL_NOTOPIC(sender->cliInfo.getNick(),
													  curChan->getName()));
	else
		reply::send_(sender->getFd(),
						 RPL_TOPIC(sender->cliInfo.getNick(),
								   curChan->getName(), curChan->getTopic()));
	if (curChan->getOpCli().empty()) {
		reply::send_(sender->getFd(), RPL_CHANOPE(sender->cliInfo.getNick(),
													  curChan->getName()));
		curChan->addCli(OPCLI, sender);
	}

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
