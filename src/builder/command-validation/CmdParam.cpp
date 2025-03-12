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
CmdParam::CmdParam(std::vector< std::string > &param, const bool opt,
				   const std::string &delim)
	: param_(param), opt_(opt), delim_(delim) {}

CmdParam::~CmdParam(void) {}

std::string &CmdParam::operator[](unsigned int i) {
	if (i >= param_.size())
		throw std::out_of_range("Param not found\n");
	return (param_[i]);
}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */
std::vector< std::string > &CmdParam::getParam(void) {
	return (param_);
}

size_t CmdParam::getParamSize(void) const {
	return (param_.size());
}

bool CmdParam::getOpt(void) const {
	return (opt_);
}

const std::string &CmdParam::getDelim() const {
	return (delim_);
}

/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */
void CmdParam::setOne(std::string &buffer) {
	param_.push_back(buffer);
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

CmdParam::ParamBuilder &
CmdParam::ParamBuilder::setDelim(const std::string &delim) {
	delim_ = delim;
	return (*this);
}

CmdParam *CmdParam::ParamBuilder::build() {
	return (new CmdParam(param_, opt_, delim_));
}
