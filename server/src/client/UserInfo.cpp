/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserInfo.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:04:27 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/23 16:23:38 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UserInfo.hpp"

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */

UserInfo::UserInfo()
	: registration_(0), name_(""), nick_("*"), pass_(""), realName_("") {}
UserInfo::~UserInfo() {}

UserInfo::UserInfo(const UserInfo &rhs) {
	static_cast< void >(rhs);
}

UserInfo &UserInfo::operator=(const UserInfo &rhs) {
	static_cast< void >(rhs);
	return *this;
}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */

const std::string &UserInfo::getName() const {
	return name_;
}

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

void UserInfo::setIP(const std::string ip) {
	ip_ = ip;
}

void UserInfo::setHostname(const std::string hostname) {
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