/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:28:52 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/04 13:39:47 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <arpa/inet.h>
#include <string.h>

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */
Client::Client(void) {}
Client::~Client() {}

Client::Client(const Client &rhs) {
	static_cast< void >(rhs);
}

Client &Client::operator=(const Client &rhs) {
	static_cast< void >(rhs);
	return *this;
}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */

int Client::getFd() const {
	return cliFd_;
}

const stringVec &Client::getJoinedChans() const {
	return (joinedChans_);
}

struct epoll_event *Client::getCliEpoll() {
	return (&cliEpoll_);
}

/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */

void Client::setFd(int fd) {
	cliFd_ = fd;
}

void Client::setCliEpoll(struct epoll_event epoll) {
	cliEpoll_.events = epoll.events;
	cliEpoll_.data.fd = epoll.data.fd;
}

void Client::removeOneChan(std::string chanName) {
	for (stringVecIt it = joinedChans_.begin(); it != joinedChans_.end(); ++it)
		if (*it == chanName) {
			joinedChans_.erase(it);
			return;
		}
}

void Client::addOneChan(std::string chanName) {
	stringVecItConst it;
	for (it = joinedChans_.begin(); it != joinedChans_.end(); ++it) {
		if (*it == chanName)
			return;
	}
	joinedChans_.push_back(chanName);
}