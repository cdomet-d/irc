/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:43 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/24 19:22:33 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Exceptions.hpp"
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

bool Channel::addClientToChan(Channel &curChan, Client &sender) {
	curChan.addCli(ALLCLI, sender);
	sender.addOneChan(curChan.getName());
	if (curChan.getOpCli().empty())
		curChan.addCli(OPCLI, sender);
	curChan.removeCli(INVITECLI, sender.getFd());
	return (true);
}

void Channel::addCli(const mapChan &curMap, Client &sender) {
	switch (curMap) {
	case ALLCLI:
		cliInChan_.insert(clientPair(sender.getFd(), &sender));
		break;
	case OPCLI:
		cliIsOperator_.insert(clientPair(sender.getFd(), &sender));
		break;
	case INVITECLI:
		cliInvited_.insert(clientPair(sender.getFd(), &sender));
	}
}

void Channel::removeCli(const mapChan &curMap, int fdCli) {
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
			Client &cli = *cliInChan_.begin()->second;
			addCli(OPCLI, cli);
			RPL::send_(cli.getFd(), RPL_MODE(oldOp.cliInfo.getPrefix(), name_,
											 "+o", cli.cliInfo.getNick()));
		}
	}
	if (cliInChan_.empty() == true) {
		server.removeChan(*this);
		delete this;
	}
}

void Channel::partOneChan(Client &sender, Channel &curChan) {
	int targetFd = sender.getFd();
	curChan.removeCli(ALLCLI, targetFd);
	sender.removeOneChan(curChan.getName());
	curChan.removeCli(OPCLI, targetFd);
	curChan.removeCli(INVITECLI, targetFd);
}

void Channel::partMess(const Client &sender, const Channel &curChan,
					   const std::string &message) {
	std::string reason = (message.empty() ? "" : ":" + message);
	RPL::sendMessageChannel(
		curChan.getCliInChan(),
		RPL_PARTREASON(sender.cliInfo.getPrefix(), curChan.getName(), reason));
}

void Channel::partAllChans(CmdSpec &cmd, const std::string &message) {
	Client &sender = cmd.getSender();
	stringVec joinedChans = sender.getJoinedChans();

	for (size_t nbChan = 0; nbChan != joinedChans.size(); nbChan++) {
		try {
			Channel &curChan = cmd.serv_.findChan(joinedChans[nbChan]);
			if (cmd.getName() == "JOIN")
				curChan.partMess(sender, curChan, message);
			curChan.partOneChan(sender, curChan);
			if (cmd.getName() == "QUIT")
				RPL::sendMessageChannel(
					curChan.getCliInChan(),
					RPL_QUIT(sender.cliInfo.getPrefix(), message));
			curChan.checkOnlyOperator(sender);
		} catch (ObjectNotFound &e) { RPL::log(RPL::ERROR, e.what()); }
	}
}

Channel &Channel::createChan(const std::string &chanName) {
	static Server &server = Server::GetServerInstance(0, "");

	try {
		Channel &curChan = server.findChan(chanName);
		return (curChan);
	} catch (ObjectNotFound &e) {
		Channel *newChan = new Channel(chanName);
		newChan->setName(chanName);
		newChan->setModes();
		server.addChan(*newChan);
		return (*newChan);
	}
}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */

const std::string &Channel::getName() const {
	return (name_);
}

const std::string &Channel::getTopic() const {
	return (topic_);
}

int Channel::getMaxCli() const {
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

const std::string &Channel::getPassword() const {
	return (pass_);
}

const std::string &Channel::getModes() const {
	return (modes_);
}

Client &Channel::getCliFromNick(const std::string &targetNick) const {
	for (clientMapIt it = cliInChan_.begin(); it != cliInChan_.end(); ++it) {
		if (it->second->cliInfo.getNick() == targetNick)
			return *it->second;
	}
	throw std::runtime_error("Client not found");
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
