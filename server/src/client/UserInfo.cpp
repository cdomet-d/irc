/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserInfo.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:04:27 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/24 10:35:10 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UserInfo.hpp"
#include "Client.hpp"
#include "Reply.hpp"
#include "printers.hpp"

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */

UserInfo::UserInfo()
	: registration_(0), nick_("*"), pass_(""), realName_("") {}
UserInfo::~UserInfo() {}

UserInfo::UserInfo(const UserInfo &rhs) {
	static_cast< void >(rhs);
}

UserInfo &UserInfo::operator=(const UserInfo &rhs) {
	static_cast< void >(rhs);
	return *this;
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */

void UserInfo::registrationCompleted(Client &sender) {
	sender.cliInfo.setRegistration(3);
	RPL::send_(sender.getFd(), RPL_WELCOME(sender.cliInfo.getNick(),
										   sender.cliInfo.getPrefix()));
	RPL::send_(sender.getFd(), RPL_YOURHOST(sender.cliInfo.getNick()));
	RPL::send_(sender.getFd(),
			   RPL_CREATED(sender.cliInfo.getNick(), print::timeStamp()));
	RPL::send_(sender.getFd(), RPL_MYINFO(sender.cliInfo.getNick()));
	RPL::send_(sender.getFd(), RPL_ISUPPORT(sender.cliInfo.getNick()));
	RPL::send_(sender.getFd(), RPL_MOTDSTART(sender.cliInfo.getNick()));
	RPL::send_(sender.getFd(), RPL_MOTD(sender.cliInfo.getNick()));
	RPL::send_(sender.getFd(), RPL_ENDOFMOTD(sender.cliInfo.getNick()));
}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */

std::string UserInfo::getNick() const {
	return nick_;
}

std::string UserInfo::getUsername() const {
	return username_;
}

std::string UserInfo::getRealName() const {
	return realName_;
}

std::string UserInfo::getIP() const {
	return (ip_);
}

std::string UserInfo::getHostname() const {
	return (hostname_);
}

std::string UserInfo::getPrefix() const {
	return (prefix_);
}

int UserInfo::getRegistration() const {
	return (registration_);
}

/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */

void UserInfo::setNick(const std::string &newNick) {
	nick_ = newNick;
}

void UserInfo::setUsername(const std::string &username) {
	username_ = username;
}

void UserInfo::setIP(std::string ip) {
	ip_ = ip;
}

void UserInfo::setHostname(std::string hostname) {
	if (!hostname.empty())
		hostname_ = hostname;
	else
		hostname_ = "NULL";
}

void UserInfo::setPrefix() {
	prefix_ = nick_ + "!" + username_ + "@" + hostname_;
}

void UserInfo::setRegistration(int stage) {
	registration_ = stage;
}

void UserInfo::setRealname(const std::string &realname) {
	realName_ = realname;
}