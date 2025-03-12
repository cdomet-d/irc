/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:28:52 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/12 14:27:15 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <arpa/inet.h>
#include <string.h>

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */
Client::~Client() {}
Client::Client(const Client &rhs) {
	static_cast< void >(rhs);
}
Client::Client(void) : name_(""), nick_(""), pass_(""), realName_("") {}
Client &Client::operator=(const Client &rhs) {
	static_cast< void >(rhs);
	return *this;
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */
stringVec Client::getCmdParam() {
	return cmdParam_;
}

int Client::getFd() const {
	return cliFd_;
}

std::string Client::getName() const {
	return name_;
}

std::string Client::getNick() const {
	return nick_;
}

std::string Client::getUsername() const {
	return username_;
}

std::string Client::getRealName() const {
	return realName_;
}

std::string Client::getIP() const {
	return (ip_);
}

std::string Client::getHostname() const {
	return (hostname_);
}

std::string Client::getPrefix() const {
	return (prefix_);
}

stringVec &Client::getJoinedChans() {
	return (joinedChans_);
}

std::string Client::getBuffer() const {
	return (buffer_);
}

struct epoll_event *Client::getCliEpoll() {
	return (&cliEpoll_);
}

/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */
void Client::setCmdParam(const stringVec &splitBuffer) {
	cmdParam_ = splitBuffer;
}

void Client::setTrailingParam(const std::string &trail) {
	cmdParam_.push_back(trail);
}


void Client::setNick(const std::string &newNick) {
	nick_ = newNick;
}

void Client::setUsername(const std::string &username) {
	username_ = username;
}

void Client::setFd(int fd) {
	cliFd_ = fd;
}

void Client::setCliEpoll(struct epoll_event epoll) {
	cliEpoll_.events = epoll.events;
	cliEpoll_.data.fd = epoll.data.fd;
}

void Client::setIP(std::string ip) {
	ip_ = ip;
}

void Client::setHostname(std::string hostname) {
	if (!hostname.empty())
		hostname_ = hostname;
	else
		hostname_ = "NULL";
}

void Client::setPrefix() {
	prefix_ = nick_ + "!" + username_ + "@" + hostname_;
}

void Client::setBuffer(std::string buffer) {
	buffer_ = buffer;
}