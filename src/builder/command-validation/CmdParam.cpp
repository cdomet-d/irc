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
	//TODO: add verif of index
	return (this->param_[i]);
}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */
std::vector< std::string > &CmdParam::getParam(void) {
	return (this->param_);
}

size_t CmdParam::getParamSize(void) const {
	return (this->param_.size());
}

/* ************************************************************************** */
/*                               NESTED CLASS                                 */
/* ************************************************************************** */
CmdParam::ParamBuilder::ParamBuilder(void) : opt_(false), delim_("") {}

CmdParam::ParamBuilder::~ParamBuilder(void) {}

/* methods */
CmdParam::ParamBuilder &CmdParam::ParamBuilder::isOpt(bool opt) {
	this->opt_ = opt;
	return (*this);
}

CmdParam::ParamBuilder &
CmdParam::ParamBuilder::setDelim(const std::string &delim) {
	this->delim_ = delim;
}

CmdParam *CmdParam::ParamBuilder::build() {
	return (new CmdParam(this->param_, this->opt_, this->delim_));
}
