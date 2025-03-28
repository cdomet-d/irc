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
CmdParam::CmdParam(void) : opt_(false), list_(false) {}

CmdParam::CmdParam(const bool opt, const bool list)
	: opt_(opt), list_(list) {}

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
		opt_ = rhs.isOpt();
		list_ = rhs.isList();
		innerParam_ = rhs.getInnerParam();
	}
	return (*this);
}

bool CmdParam::empty() {
	return innerParam_.begin() == innerParam_.end();
}

size_t CmdParam::size(void) const {
	return (innerParam_.size());
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

bool CmdParam::isOpt(void) const {
	return (opt_);
}

bool CmdParam::isList(void) const {
	return (list_);
}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */
const stringVec &CmdParam::getInnerParam(void) const {
	return (innerParam_);
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
