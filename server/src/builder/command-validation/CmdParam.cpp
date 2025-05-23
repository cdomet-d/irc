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
CmdParam::CmdParam() : opt_(false), list_(false) {}

CmdParam::CmdParam(const bool opt, const bool list) : opt_(opt), list_(list) {}

CmdParam::CmdParam(const CmdParam &rhs) {
	*this = rhs;
}

CmdParam::~CmdParam() {}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */
std::string &CmdParam::operator[](size_t i) {
	if (i >= innerParam_.size())
		throw std::out_of_range("Param not found");
	return (innerParam_[i]);
}

const std::string &CmdParam::operator[](size_t i) const {
	if (i >= innerParam_.size())
		throw std::out_of_range("Param not found");
	return (innerParam_[i]);
}

CmdParam &CmdParam::operator=(const CmdParam &rhs) {
	if (this != &rhs) {
		opt_ = rhs.isOpt();
		list_ = rhs.isList();
		innerParam_ = rhs.getInnerParam();
	}
	return (*this);
}

bool CmdParam::empty() {
	return innerParam_.begin() == innerParam_.end();
}

size_t CmdParam::size() const {
	return (innerParam_.size());
}

void CmdParam::rmParam(size_t pos) {
	innerParam_.erase(innerParam_.begin() + pos);
}

void CmdParam::addOne(size_t pos) {
	innerParam_.insert(innerParam_.begin() + pos, "");
}

void CmdParam::clean() {
	innerParam_.clear();
}

bool CmdParam::isOpt() const {
	return (opt_);
}

bool CmdParam::isList() const {
	return (list_);
}

bool CmdParam::trimParam(size_t paramIdx, size_t lenToTrim) {
	if (innerParam_[paramIdx].size() > lenToTrim)
		innerParam_[paramIdx].erase(lenToTrim);
	return (true);
}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */
const stringVec &CmdParam::getInnerParam() const {
	return (innerParam_);
}

/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */
void CmdParam::setOneParam(std::string &buffer) {
	innerParam_.push_back(buffer);
}

void CmdParam::setParamList(const stringVec &buffer) {
	if (!buffer.empty())
		innerParam_ = buffer;
}
