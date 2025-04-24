/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:16:46 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/24 16:51:12 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"
#include "Server.hpp"
#include "printers.hpp"
#include <algorithm>

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */

Message::Message() {}

Message::~Message() {}

std::string &Message::operator[](unsigned int i) {
	if (i >= cmdParam_.size())
		throw std::out_of_range("Param not found");
	return (cmdParam_[i]);
}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */
/* returns the string vector associated with the command being processed */
const stringVec &Message::getCmdParam() const {
	return cmdParam_;
}

/* returns the command being processed */
const std::string &Message::getCmd() const {
	return cmdParam_.at(0);
}

/* the unprocessed message */
const std::string &Message::getMess() const {
	return message_;
}

/* in the event where several messages separated by /r/n were sent, the leftover
 * part of the raw message */
const std::string &Message::getLeft() const {
	return leftover_;
}

/* returns the size of the string vector holding the command and its parameters */
size_t Message::getSize() const {
	return cmdParam_.size();
}

/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */

/* sets the string vector holding the command and its parameters */
void Message::setCmdParam(const stringVec &splitBuffer) {
	cmdParam_ = splitBuffer;
	if (!trailing_.empty())
		cmdParam_.push_back(trailing_.substr(1, trailing_.size()));
}

/* sets the buffer containing the raw message */
void Message::setMess(const std::string &buffer) {
	message_ = buffer;
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */

/* makes mode parameters usable by builder pattern */
void Message::formatMode() {
	if (cmdParam_.size() < 2)
		return;

	stringVec modeformat;
	std::string flagformat, paramformat;

	modeformat.push_back(cmdParam_.at(0));
	modeformat.push_back(cmdParam_.at(1));

	if (cmdParam_.size() > 2 && !cmdParam_.at(2).empty())
		formatModeFlags(flagformat);
	if (cmdParam_.size() > 3 && !cmdParam_.at(3).empty())
		formatModeParam(paramformat);
	assignFormattedMode(flagformat, paramformat, modeformat);
}

/* loops on cmdParam_[2], which is where the flags are supposed to be */
void Message::formatModeFlags(std::string &flagformat) {
	std::string flags = cmdParam_.at(2);
	for (size_t i = 0; i < flags.size(); i++) {
		const char firstChar = flags[i];
		if (firstChar == '+' || firstChar == '-') {
			i++;
			while (i < flags.size()) {
				flagformat += firstChar;
				flagformat += flags[i];
				if (i + 1 != flags.size())
					flagformat += ',';
				if ((i + 1) < flags.size() &&
					(flags[i + 1] == '+' || flags[i + 1] == '-'))
					break;
				++i;
			}
		} else {
			flagformat += flags[i];
			if (i < flags.size() &&
				(flags[i + 1] == '+' || flags[i + 1] == '-'))
				flagformat += ',';
		}
	}
}

/* loops on cmdParam_, starting .at(3) , where the remaining strings are considered mode parameters */
void Message::formatModeParam(std::string &paramformat) {
	for (stringVec::iterator it = cmdParam_.begin() + 3; it != cmdParam_.end();
		 ++it) {
		if (!it->empty()) {
			paramformat += *it;
			if ((it + 1) != cmdParam_.end())
				paramformat += ',';
		}
	}
}

/* updates cmdParam_ with newly formatted strings */
void Message::assignFormattedMode(const std::string &flagformat,
								  const std::string &paramformat,
								  stringVec &modeformat) {
	if (!flagformat.empty())
		modeformat.push_back(flagformat);
	else if (cmdParam_.size() > 2)
		modeformat.push_back("");
	if (!paramformat.empty())
		modeformat.push_back(paramformat);
	clearCmdParam();
	cmdParam_ = modeformat;
}

/* Clears the stringVec CmdParam_ */
void Message::clearCmdParam() {
	for (stringVec::iterator i = cmdParam_.begin(); i != cmdParam_.end();) {
		cmdParam_.erase(i);
	}
	cmdParam_.clear();
}

/* clears the raw received message and the trailing */
void Message::clearMess() {
	message_.clear();
	trailing_.clear();
}

/* clears every buffer contained in Mess */
void Message::clear() {
	clearMess();
	clearCmdParam();
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

/* Assess whether received message has a trailing parameter, in which case it 
is removed and stored in mess.trailing to preserve it from vectorSplit*/
bool Message::hasTrailing() {
	std::string::size_type trail = message_.find(" :");

	if (trail != std::string::npos) {
		trailing_ = message_.substr((trail) + 1, message_.size());
		message_.erase(trail);
		return true;
	}
	return false;
}

bool Message::hasValidLen(const Client &sender) {
	if (message_.empty())
		return false;
	if (message_.size() > 510) {
		RPL::send_(sender.getFd(), ERR_INPUTTOOLONG(sender.cliInfo.getNick()));
		return false;
	}
	return true;
}

/* Determine whether the received messages has \r\n, \n or \r as a termination;
returns the size of the found termination to accurately trim it from the raw message */
std::string::size_type Message::evaluateTermination(std::string &term) const {
	if (message_.find("\r\n") != std::string::npos) {
		term = "\r\n";
		return 2;
	}
	if (message_.find("\n") != std::string::npos) {
		term = "\n";
		return 1;
	}
	if (message_.find("\r") != std::string::npos) {
		term = "\r";
		return 1;
	}
	return std::string::npos;
}

/* Trims termination from message */
void Message::removeNewlines() {
	std::string term;

	if (evaluateTermination(term) == std::string::npos) {
		message_.clear();
		return;
	}
	std::string::size_type newline = message_.find(term);
	leftover_ = message_.substr(newline + term.size());
	message_.erase(newline);
}

static bool isConsecutiveSpace(char left, char right) {
	return (left == ' ' && right == ' ');
}

/* Removes consecutive spaces */
void Message::trimSpaces() {
	std::string::iterator newEnd =
		std::unique(message_.begin(), message_.end(), isConsecutiveSpace);
	if (newEnd != message_.end())
		message_.erase(newEnd, message_.end());
}

/* Makes lowercases commands exploitable */
void Message::cmdToUpper() {
	std::string &cmd = cmdParam_.at(0);
	std::transform(cmd.begin(), cmd.end(), cmd.begin(),
				   (int (*)(int))std::toupper);
}

/* Assesses whether buff is empty */
bool Message::buffIsEmpty() {
	return message_.begin() == message_.end();
}

/* Assesses whether received command is CAP */
bool Message::isCap() {
	return message_.find("CAP") != std::string::npos;
}

/* In the event that the server received several messages in a single buffer, 
updates the message to move on to the next command */
void Message::updateMess() {
	message_ = leftover_;
	leftover_.clear();
}
