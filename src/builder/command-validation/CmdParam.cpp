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
CmdParam::CmdParam(stringVec &param, const bool opt, const std::string& delim)
	: opt_(opt), delim_(delim), param_(param) {}

CmdParam::CmdParam(const CmdParam &rhs) {
	*this = rhs;
}

CmdParam::~CmdParam(void) {}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */
std::string &CmdParam::operator[](unsigned int i) {
	if (i >= param_.size())
		throw std::out_of_range("Param not found");
	return (param_[i]);
}

CmdParam &CmdParam::operator=(const CmdParam &rhs) {
	if (this != &rhs) {
		opt_ = rhs.getOpt();
		delim_ = rhs.getDelim();
		param_ = rhs.getParam();
	}
	return (*this);
}

void CmdParam::rmParam(unsigned int pos) {
	param_.erase(param_.begin() + pos);
}

void CmdParam::rmParam(stringVec::iterator begin, stringVec::iterator end) {
	param_.erase(begin, end);
}

void CmdParam::addOne(unsigned int pos) {
	param_.insert(param_.begin() + pos, "");
}

void CmdParam::clean(void) {
	param_.clear();
}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */
const stringVec &CmdParam::getParam(void) const {
	return (param_);
}

size_t CmdParam::getSize(void) const {
	return (param_.size());
}

bool CmdParam::getOpt(void) const {
	return (opt_);
}

const std::string &CmdParam::getDelim(void) const {
	return (delim_);
}

/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */
void CmdParam::setOne(std::string &buffer) {
	param_.push_back(buffer);
}

void CmdParam::setList(const stringVec &buffer) {
	param_ = buffer;
}

/* ************************************************************************** */
/*                               NESTED CLASS                                 */
/* ************************************************************************** */
CmdParam::ParamBuilder::ParamBuilder(void) : opt_(false), delim_("") {}

CmdParam::ParamBuilder::~ParamBuilder(void) {}

/* methods */
CmdParam::ParamBuilder &CmdParam::ParamBuilder::isOpt(bool opt) {
	opt_ = opt;
	return (*this);
}

CmdParam::ParamBuilder &CmdParam::ParamBuilder::isList(const std::string& delim) {
	delim_ = delim;
	return (*this);
}

CmdParam *CmdParam::ParamBuilder::build() {
	return (new CmdParam(param_, opt_, delim_));
}
