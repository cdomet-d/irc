/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:16:46 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/14 14:46:33 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */

Message::Message(void) {}

Message::~Message(void) {}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */
stringVec &Message::getCmdParam() {
	return cmdParam_;
}

std::string Message::getCmd() const {
	return cmdParam_.at(0);
}

std::string Message::getBuffer() const {
	return buffer_;
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
	// cmdParam_.clear();
}
void Message::clearBuffer() {
	buffer_.clear();
}