/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserInfo.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:04:27 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/24 15:35:41 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UserInfo.hpp"
#include "Client.hpp"
#include "Reply.hpp"
#include "printers.hpp"

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */

UserInfo::UserInfo() : registration_(0), nick_("*"), pass_(""), realName_("") {}
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

const std::string &UserInfo::getNick() const {
	return nick_;
}

const std::string &UserInfo::getUsername() const {
	return username_;
}

const std::string &UserInfo::getRealName() const {
	return realName_;
}

const std::string &UserInfo::getIP() const {
	return (ip_);
}

const std::string &UserInfo::getHostname() const {
	return (hostname_);
}

const std::string &UserInfo::getPrefix() const {
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

void UserInfo::setIP(const std::string &ip) {
	ip_ = ip;
}

void UserInfo::setHostname(const std::string &hostname) {
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