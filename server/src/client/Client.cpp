/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:28:52 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/24 15:34:22 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <arpa/inet.h>
#include <string.h>

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */
Client::Client() {}
Client::~Client() {}

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

void Client::removeOneChan(const std::string &chanName) {
	for (stringVecIt it = joinedChans_.begin(); it != joinedChans_.end(); ++it)
		if (*it == chanName) {
			joinedChans_.erase(it);
			return;
		}
}

void Client::addOneChan(const std::string &chanName) {
	stringVecItConst it;
	for (it = joinedChans_.begin(); it != joinedChans_.end(); ++it) {
		if (*it == chanName)
			return;
	}
	joinedChans_.push_back(chanName);
}