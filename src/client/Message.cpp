/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:16:46 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/07 09:08:07 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"
#include "Server.hpp"
#include <algorithm>

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
/* the string vector associated with the command being processed */
const stringVec &Message::getCmdParam() {
	return cmdParam_;
}

/* the command being processed */
const std::string Message::getCmd() const {
	return cmdParam_.at(0);
}

/* the unprocessed message */
const std::string Message::getMess() const {
	return message_;
}

/* in the event where several messages separated by /r/n were sent, the leftover part of the raw message */
const std::string Message::getLeft() const {
	return leftover_;
}

size_t Message::getSize() const {
	return cmdParam_.size();
}

/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */

void Message::setCmdParam(const stringVec &splitBuffer) {
	cmdParam_ = splitBuffer;
	if (!trailing_.empty())
		cmdParam_.push_back(trailing_);
}

void Message::setMess(std::string buffer) {
	message_ = buffer;
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
void Message::clearMess() {
	message_.clear();
	trailing_.clear();
}

void Message::formatMode() {
	if (cmdParam_.size() < 2)
		return;

	stringVec modeFormat;
	std::string flagformat, paramformat;

	modeFormat.push_back(cmdParam_.at(0));
	modeFormat.push_back(cmdParam_.at(1));

	for (stringVec::iterator i = cmdParam_.begin() + 2; i != cmdParam_.end();
		 ++i) {
		if (!i->empty()) {
			const char firstChar = (*i)[0];
			if (firstChar == '+' || firstChar == '-') {
				std::string flags = *i;
				for (size_t j = 1; j < flags.size(); ++j) {
					flagformat += firstChar;
					flagformat += (*i)[j];
					flagformat += ',';
				}
			} else {
				paramformat += *i;
				paramformat += ',';
			}
		}
	}
	if (!flagformat.empty())
		modeFormat.push_back(flagformat);
	if (!paramformat.empty())
		modeFormat.push_back(paramformat);
	clearCmdParam();
	cmdParam_ = modeFormat;
}

bool Message::hasPrefix(const std::string &cliPrefix) {
	if (message_.at(0) == ':') {
		std::string::size_type sep = message_.find(" ");
		if (sep != std::string::npos) {
			std::string prefix = message_.substr(1, (sep - 1));
			if (prefix != cliPrefix)
				return false;
			else
				message_.erase(0, (sep + 1));
		}
	}
	return true;
}

bool Message::hasTrailing() {
	std::string::size_type trail = message_.find(" :");

	if (trail != std::string::npos) {
		trailing_ = message_.substr((trail) + 2, message_.size());
		message_.erase(trail);
		return true;
	}
	return false;
}

bool Message::lenIsValid(const Client &sender) {
	if (message_.empty())
		return false;
	if (message_.size() > 512) {
		reply::send_(sender.getFd(),
					 ERR_INPUTTOOLONG(sender.cliInfo.getNick()));
		return false;
	}
	return true;
}

std::string::size_type Message::evaluateTermination() const {
	if (message_.find("\r\n") != std::string::npos)
		return 2;
	if (message_.find("\n") != std::string::npos)
		return 1;
	return std::string::npos;
}

void Message::removeNewlines() {
	std::string::size_type termSize = evaluateTermination();
	if (termSize == std::string::npos) {
		message_.clear();
		return;
	}
	std::string::size_type newline =
		(termSize == 2 ? message_.find("\r\n") : message_.find("\n"));
	leftover_ = message_.substr(newline + termSize);
	message_.erase(message_.begin() + newline, message_.end());
	return;
}
static bool isConsecutiveSpace(char left, char right) {
	return (left == ' ' && right == ' ');
}
void Message::trimSpaces() {
	std::string::iterator newEnd =
		std::unique(message_.begin(), message_.end(), isConsecutiveSpace);
	if (newEnd != message_.end())
		message_.erase(newEnd, message_.end());
}

bool Message::emptyBuff() {
	return message_.begin() == message_.end();
}

bool Message::isCap() {
	return message_.find("CAP") != std::string::npos;
}

void Message::updateMess() {
	message_ = leftover_;
	leftover_.clear();
}
