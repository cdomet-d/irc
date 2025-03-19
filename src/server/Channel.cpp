/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:43 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/19 16:23:58 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Server.hpp"

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */

Channel::Channel(std::string name)
	: inviteOnly_(false), isPassMatch_(false), topicRestrict_(true), maxCli_(0),
	  name_(name), topic_("")
{
	setModes();
}

Channel::~Channel(void)
{
	// logLevel(INFO, "Channel deleted:", this->getName());
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */

void sendMessageChannel(clientMap allCliChannel, std::string message)
{
	for (clientMapIt it = allCliChannel.begin(); it != allCliChannel.end();
		 ++it) {
		sendReply(it->second->getFd(), message);
	}
}

bool Channel::addClientToChan(Channel *curChan, Client *curCli)
{
	// logLevel(DEBUG, "-----addClientToChan-----");
	std::map< int, Client * > &clients = curChan->getCliInChan();
	for (clientMapIt it = clients.begin(); it != clients.end(); ++it)
		if (curCli == it->second) {
			// logLevel(INFO, "Client already in channel");
			return (false);
		}
	if (curChan->getCliInChan().empty())
		curChan->addCli(OPCLI, curCli);
	curChan->addCli(ALLCLI, curCli);

	curCli->getJoinedChans().push_back(curChan->getName());

	//messageToAllChannel
	sendMessageChannel(curChan->getCliInChan(),
					   RPL_JOIN(curCli->cliInfo.getNick(), curChan->getName()));

	if (curChan->getTopic().empty() == true)
		sendReply(curCli->getFd(),
				  RPL_NOTOPIC(curCli->cliInfo.getNick(), curChan->getName()));
	else
		sendReply(curCli->getFd(),
				  RPL_TOPIC(curCli->cliInfo.getNick(), curChan->getName(),
							curChan->getTopic()));
	return (true);
}

void Channel::addCli(mapChan curMap, Client *curCli) {
	switch (curMap) {
		case ALLCLI:
			cliInChan_.insert(clientPair(curCli->getFd(), curCli));
			break ;
		case OPCLI:
			cliIsOperator_.insert(clientPair(curCli->getFd(), curCli));
			break ;
		case INVITECLI:
			cliInvited_.insert(clientPair(curCli->getFd(), curCli));
	}
}

void Channel::removeCli(mapChan curMap, int fdCli) {
	switch (curMap) {
		case ALLCLI:
			cliInChan_.erase(fdCli);
			break ;
		case OPCLI:
			cliIsOperator_.erase(fdCli);
			break ;
		case INVITECLI:
			cliInvited_.erase(fdCli);
	}
}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */

std::string Channel::getName() const
{
	return (name_);
}
std::string Channel::getTopic() const
{
	return (topic_);
}
int Channel::getMaxCli() const
{
	return (maxCli_);
}
bool Channel::getInviteOnly() const
{
	return (inviteOnly_);
}
bool Channel::getIsPassMatch() const
{
	return (isPassMatch_);
}
bool Channel::getTopicRestrict() const
{
	return (topicRestrict_);
}
clientMap &Channel::getCliInChan()
{
	return (cliInChan_);
}
clientMap &Channel::getOpCli()
{
	return (cliIsOperator_);
}
clientMap &Channel::getInvitCli()
{
	return (cliInvited_);
}
std::string Channel::getPassword() const
{
	return (pass_);
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
	name_ = name;
}
void Channel::setTopic(std::string topic)
{
	topic_ = topic;
}
void Channel::setPassword(std::string password)
{
	pass_ = password;
}
void Channel::setModes()
{
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
void Channel::setMaxCli(int maxCli)
{
	maxCli_ = maxCli;
}
void Channel::setInviteOnly(bool inviteOnly)
{
	inviteOnly_ = inviteOnly;
}
void Channel::setIsPassMatch(bool password)
{
	isPassMatch_ = password;
}
void Channel::setTopicRestrict(bool topicRestrict)
{
	topicRestrict_ = topicRestrict;
}
