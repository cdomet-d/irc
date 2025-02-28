/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:28:52 by aljulien          #+#    #+#             */
/*   Updated: 2025/02/28 16:09:09 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <arpa/inet.h>
#include <string.h>

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */
Client::~Client() {}
Client::Client(const Client &rhs)
{
	static_cast< void >(rhs);
}
Client::Client(void) : _name(""), _nick(""), _pass(""), _realName("") {}
Client &Client::operator=(const Client &rhs)
{
	static_cast< void >(rhs);
	return *this;
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */
int Client::getFd() const
{
	return _cliFd;
}
std::string Client::getName() const
{
	return _name;
}
std::string Client::getNick() const
{
	return _nick;
}
std::string Client::getUsername() const
{
	return _username;
};
std::string Client::getRealName() const
{
	return _realName;
}
struct epoll_event *Client::getCliEpoll()
{
	return (&_cliEpoll);
}
std::string Client::getIP() const
{
	return (_cliIP);
}
std::string Client::getHostname() const {
	return (_cliHostname);
}
std::string Client::getPrefix() const {
	return (_prefix);
}

/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */
void Client::setNick(const std::string &newNick)
{
	_nick = newNick;
}
void Client::setUsername(const std::string &username)
{
	_username = username;
}
void Client::setFd(int fd)
{
	_cliFd = fd;
}
void Client::setCliEpoll(struct epoll_event epoll)
{
	_cliEpoll.events = epoll.events;
	_cliEpoll.data.fd = epoll.data.fd;
}
void Client::setIP(std::string ip) {
	_cliIP = ip;
}
void Client::setHostname(std::string hostname) {
	if (!hostname.empty())
		_cliHostname = hostname;
	else
		_cliHostname = "NULL";
}
void Client::setPrefix() {
	_prefix = _nick + "!" + _username + "@" + _cliHostname;
}