/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:43 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/15 14:30:06 by cdomet-d         ###   ########.fr       */
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

Channel::~Channel() {
	// RPL::INFO, "Channel deleted:", this->getName());
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */

void sendMessageChannel(clientMap allCliChannel, std::string message) {
	for (clientMapIt it = allCliChannel.begin(); it != allCliChannel.end();
		 ++it) {
		RPL::send_(it->second->getFd(), message);
	}
}

bool Channel::addClientToChan(Channel *curChan, Client *sender) {
	curChan->addCli(ALLCLI, sender);
	sender->addOneChan(curChan->getName());
	if (curChan->getOpCli().empty())
		curChan->addCli(OPCLI, sender);
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

void Channel::checkOnlyOperator(Client &oldOp) {
	static Server &server = Server::GetServerInstance(0, "");

	if (cliInChan_.size() >= 1) {
		if (!cliIsOperator_.size()) {
			Client *cli = cliInChan_.begin()->second;
			addCli(OPCLI, cli);
			RPL::send_(cli->getFd(), RPL_MODE(oldOp.cliInfo.getPrefix(), name_,
											  "+o", cli->cliInfo.getNick()));
		}
	}
	if (cliInChan_.empty() == true) {
		server.removeChan(this);
		delete this;
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

	if (static_cast< ssize_t >(getMaxCli()) != -1)
		modes.append("l");
	if (getInviteOnly() == true)
		modes.append("i");
	if (getIsPassMatch() == true)
		modes.append("k");
	if (getTopicRestrict() == true)
		modes.append("t");
	modes_ = modes;
	if (modes_ == "+")
		modes_.clear();
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
