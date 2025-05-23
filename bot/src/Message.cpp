/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:24:10 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/25 09:44:14 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */

Msg::~Msg(void) {}

Msg::Msg(void) {}

Msg::Msg(const Msg &rhs) {
	*this = rhs;
}

Msg &Msg::operator=(const Msg &rhs) {
	(void)rhs;
	return *this;
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */

bool Msg::rplIs(const std::string &expected) const {
	return rcv_.find(expected) != std::string::npos;
}

ssize_t Msg::_recv(const int fd) {
	return recv(fd, rcvbuf, sizeof(rcvbuf) - 1, 0);
}

bool Msg::processBuf() {
	removeNl();
	trimConsecutiveSpaces();
	cmdParam_ = vectorSplit(rcv_, ' ');
	trimUsername();
	return true;
}

/* ************************************************************************** */
/*                               UTILS                                        */
/* ************************************************************************** */

static bool isConsecutiveSpace(char left, char right) {
	return (left == ' ' && right == ' ');
}

void Msg::removeNl() {
	std::string::size_type newline = rcv_.find("\r\n");
	rcv_.erase(rcv_.begin() + newline, rcv_.end());
	return;
}

void Msg::trimConsecutiveSpaces() {
	std::string::iterator newEnd =
		std::unique(rcv_.begin(), rcv_.end(), isConsecutiveSpace);
	if (newEnd != rcv_.end())
		rcv_.erase(newEnd, rcv_.end());
}

void Msg::clear() {
	std::memset(rcvbuf, 0, sizeof(rcvbuf));
	rcv_.clear();
}

void Msg::clearCmdParam() {
	for (stringVec::iterator i = cmdParam_.begin(); i != cmdParam_.end();)
		cmdParam_.erase(i);
	cmdParam_.clear();
}

void Msg::trimUsername() {
	cmdParam_[prefix_].erase(cmdParam_[prefix_].begin());
	if (cmdParam_[prefix_].find('!') != std::string::npos)
		cmdParam_[prefix_].erase(cmdParam_[prefix_].find('!'));
}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */

const std::string &Msg::getRcv() const {
	return rcv_;
}

/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */

void Msg::setRcv() {
	rcv_ = rcvbuf;
}
