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
CmdParam::CmdParam(void) : opt_(false), delim_('\0') {}

CmdParam::CmdParam(const bool opt, const char delim)
	: opt_(opt), delim_(delim) {}

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

char CmdParam::getDelim(void) const {
	return (delim_);
}

/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */
void CmdParam::setOneParam(std::string &buffer) {
	innerParam_.push_back(buffer);
}

void CmdParam::setParamList(const stringVec &buffer) {
	innerParam_ = buffer;
}
