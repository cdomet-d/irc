/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdParam.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:14:44 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/07 17:00:37 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdParam.hpp"

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */
CmdParam::CmdParam(stringVec &param, const bool opt, const char delim)
	: opt_(opt), delim_(delim), innerParam_(param) {}

CmdParam::CmdParam(const CmdParam &rhs) {
	*this = rhs;
}

CmdParam::~CmdParam(void) {}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */
std::string &CmdParam::operator[](unsigned int i) {
	if (i >= innerParam_.size())
		throw std::out_of_range("Param not found");
	return (innerParam_[i]);
}

CmdParam &CmdParam::operator=(const CmdParam &rhs) {
	if (this != &rhs) {
		opt_ = rhs.getOpt();
		delim_ = rhs.getDelim();
		innerParam_ = rhs.getInnerParam();
	}
	return (*this);
}

void CmdParam::rmParam(unsigned int pos) {
	innerParam_.erase(innerParam_.begin() + pos);
}

void CmdParam::rmParam(stringVec::iterator begin, stringVec::iterator end) {
	innerParam_.erase(begin, end);
}

void CmdParam::addOne(unsigned int pos) {
	innerParam_.insert(innerParam_.begin() + pos, "");
}

void CmdParam::clean(void) {
	innerParam_.clear();
}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */
const stringVec &CmdParam::getInnerParam(void) const {
	return (innerParam_);
}

size_t CmdParam::getSize(void) const {
	return (innerParam_.size());
}

bool CmdParam::getOpt(void) const {
	return (opt_);
}

const char CmdParam::getDelim(void) const {
	return (delim_);
}

/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */
void CmdParam::setOne(std::string &buffer) {
	innerParam_.push_back(buffer);
}

/*
stringVec vectorSplit(std::string &s,
									   const std::string &del) {
	stringVec inputCli;
	size_t pos = 0;
	std::string token;

	while ((pos = s.find(del)) != std::string::npos) {
		token = s.substr(0, pos);
		inputCli.push_back(token);
		s.erase(0, pos + del.length());
	}
	return (inputCli);
}
*/

static const stringVec splitInnerParam(std::string &s, char delim) {
	stringVec buffer;
	size_t pos = 0;
	std::string del(1, delim);
	std::string sub;

	for (size_t i = 0; i < s.size(); i++) {
		pos = s.find_first_of(del + ":");
		if (pos != std::string::npos)
			sub = s.substr(0, pos);
		buffer.push_back(sub);
		if (s[pos] == ':' && (pos != 0 && s[pos - 1] == ' ')) {
			s.erase(0, pos);
			sub = s.substr(pos, s.size());
			buffer.push_back(sub);
			return (buffer);
		}
		s.erase(0, pos + 1);
	}
	return (buffer);
}

void CmdParam::setList() {
	try {
		// const stringVec &buffer = splitInnerParam(innerParam_[0], delim_);
		// innerParam_ = buffer;
	} catch (const std::out_of_range &e) {};
}

/* ************************************************************************** */
/*                               NESTED CLASS                                 */
/* ************************************************************************** */
CmdParam::ParamBuilder::ParamBuilder(void) : opt_(false), delim_('\0') {}

CmdParam::ParamBuilder::~ParamBuilder(void) {}

/* methods */
CmdParam::ParamBuilder &CmdParam::ParamBuilder::isOpt(bool opt) {
	opt_ = opt;
	return (*this);
}

CmdParam::ParamBuilder &CmdParam::ParamBuilder::isList(const char delim) {
	delim_ = delim;
	return (*this);
}

CmdParam *CmdParam::ParamBuilder::build() {
	return (new CmdParam(innerParam_, opt_, delim_));
}
