/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdSpec.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:13:50 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/07 17:03:55 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdSpec.hpp"

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */
CmdSpec::CmdSpec(const std::string name, int registrationStage, paramMap params,
				 std::vector< int (*)(CmdSpec &) > checkers,
				 void (*cmExecutor)(CmdSpec &cmd))
	: name_(name) {
	registrationStage_ = registrationStage;
	params_ = params;
	checkers_ = checkers;
	cmExecutor_ = cmExecutor;
	valid_ = true;
	sender_ = NULL;
}

CmdSpec::~CmdSpec(void) {}

CmdParam &CmdSpec::operator[](e_param type) {

	for (size_t i = 0; i < params_.size(); i++) {
		if (params_[i].first == type)
			return ((*params_[i].second));
	}
	throw std::out_of_range("Param not found\n");
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */

bool CmdSpec::enoughParams() {
	if (name_ != "NICK" && name_ != "PRIVMSG") {
		for (size_t i = 0; i < params_.size(); i++) {
			CmdParam &params = *params_[i].second;
			if (!params.getOpt() && params.getParam().empty()) {
				i++;
				if (name_ == "INVITE" && params.getParam().empty())
					return (true);
				ERR_NEEDMOREPARAMS((*sender_).getNick(), name_);
				valid_ = false;
				return (false);
			}
		}
	}
	return (true);
}

CmdSpec &CmdSpec::process(std::vector< std::string > &buffer, Client &client) {

	setSender(client);
	if ((*sender_).getRegistration() < registrationStage_) {
		valid_ = false;
		if (name_ != "PASS" && name_ != "NICK" && name_ != "USER")
			ERR_NOTREGISTERED;
		return (*this);
	}
	for (size_t i = 0; i < params_.size(); i++) {
		(*params_[i].second).setOne(buffer[i]);
	}
	if (!enoughParams())
		return (*this);
	for (size_t i = 0; i < params_.size(); i++) {
		CmdParam &params = *params_[i].second;
		if (!params.getDelim().empty()) {
			params.setList(vectorSplit(params[0], params.getDelim()));
		}
	}
	for (size_t i = 0; i < checkers_.size(); i++) {
		checkers_[i](*this);
		if (!valid_)
			return (*this);
	}
	return (*this);
}

void CmdSpec::clean(void) {}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */
const std::string &CmdSpec::getName(void) const {
	return (name_);
}

bool CmdSpec::getValid(void) const {
	return (valid_);
}

void (*CmdSpec::getExecutor(void) const)(CmdSpec &cmd) {
	return (cmExecutor_);
}

/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */
void CmdSpec::setSender(Client &sender) {
	sender_ = &sender;
}

/* ************************************************************************** */
/*                               NESTED CLASS                                 */
/* ************************************************************************** */
CmdSpec::CmdBuilder::CmdBuilder(void) {
	name_ = "";
	registrationStage_ = 0;
	cmExecutor_ = NULL;
}

CmdSpec::CmdBuilder::~CmdBuilder(void) {}

/* methods */
CmdSpec::CmdBuilder &CmdSpec::CmdBuilder::Name(const std::string &name) {
	name_ = name;
	return (*this);
}

CmdSpec::CmdBuilder &CmdSpec::CmdBuilder::Registration(int stage) {
	registrationStage_ = stage;
	return (*this);
}

CmdSpec::CmdBuilder &CmdSpec::CmdBuilder::Parameters(e_param type,
													 CmdParam *param) {
	params_.push_back(std::make_pair(type, param));
	return (*this);
}

CmdSpec::CmdBuilder &CmdSpec::CmdBuilder::addChecker(int (*ft)(CmdSpec &cmd)) {
	checkers_.push_back(ft);
	return (*this);
}

CmdSpec::CmdBuilder &CmdSpec::CmdBuilder::CmExecutor(void (*ft)(CmdSpec &cmd)) {
	cmExecutor_ = ft;
	return (*this);
}

CmdSpec *CmdSpec::CmdBuilder::build() {
	return (new CmdSpec(name_, registrationStage_, params_, checkers_,
						cmExecutor_));
}
