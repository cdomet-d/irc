/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserInfo.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:04:27 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/04 13:39:48 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UserInfo.hpp"

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */

UserInfo::UserInfo(void)
	: registration_(0), name_(""), nick_("*"), pass_(""), realName_("") {}
UserInfo::~UserInfo(void) {}

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

std::string UserInfo::getName() const {
	return name_;
}

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
