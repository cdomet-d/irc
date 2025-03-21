/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:16:46 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/21 09:57:49 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"
#include "Server.hpp"
#include <iostream>

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */

Message::Message(void) {}

Message::~Message(void) {}

std::string &Message::operator[](unsigned int i) {
	if (i >= cmdParam_.size())
		throw std::out_of_range("Param not found");
	return (cmdParam_[i]);
}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */
const stringVec &Message::getCmdParam() {
	return cmdParam_;
}

const std::string Message::getCmd() const {
	return cmdParam_.at(0);
}

const std::string Message::getBuffer() const {
	return buffer_;
}

size_t Message::getSize() const {
	return cmdParam_.size();
}

/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */

void Message::setCmdParam(const stringVec &splitBuffer) {
	cmdParam_ = splitBuffer;
}

void Message::setTrailingParam(const std::string &trail) {
	cmdParam_.push_back(trail);
}

void Message::setBuffer(std::string buffer) {
	buffer_ = buffer;
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */
void Message::clearCmdParam() {
	for (stringVec::iterator i = cmdParam_.begin(); i != cmdParam_.end();) {
		cmdParam_.erase(i);
	}
	cmdParam_.clear();
}
void Message::clearBuffer() {
	buffer_.clear();
}