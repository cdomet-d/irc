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

CmdSpec::~CmdSpec(void) {
	for (paramMap::iterator it = params_.begin(); it != params_.end(); it++) {
		delete it->second;
	}
}

CmdParam &CmdSpec::operator[](e_param type) {
	paramMap::iterator it = params_.begin();

	it = params_.find(type);
	if (it == params_.end())
		throw std::out_of_range("Param not found\n");
	return (*it->second);
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */

bool CmdSpec::enoughParams() {
	if (name_ != "NICK" && name_ != "PRIVMSG") {
		for (paramMap::iterator it = params_.begin(); it != params_.end();
			 it++) {
			CmdParam &params = *it->second;
			if (!params.getOpt() && params.getParam().empty()) {
				it++;
				if (name_ == "INVITE" && params.getParam().empty())
					return (true);
				std::cout << ERR_NEEDMOREPARAMS((*sender_).getNick(), name_);
				valid_ = false;
				return (false);
			}
		}
	}
	return (true);
}

CmdSpec &CmdSpec::process(stringVec &buffer, Client &client) {
	setSender(client);
	if ((*sender_).getRegistration() < registrationStage_) {
		valid_ = false;
		if (name_ != "PASS" && name_ != "NICK" && name_ != "USER")
			std::cout << ERR_NOTREGISTERED;
		return (*this);
	}
	size_t i = 0;
	paramMap::iterator it = params_.begin();
	while (it != params_.end() && i < buffer.size()) {
		(*it->second).setOne(buffer[i]);
		it++;
		i++;
	}
	if (!enoughParams())
		return (*this);
	for (paramMap::iterator ite = params_.begin(); ite != params_.end();
		 ite++) {
		CmdParam &params = *ite->second;
		if (params.getList()) {
			params.setList(vectorSplit(params[0], ","));
		}
	}

	i = 0;
	for (paramMap::iterator ite = params_.begin(); ite != params_.end();
		 ite++) {
			std::cout << "param[" << i << "] :\n";
			for (size_t index = 0; index < (*ite->second).getParamSize(); index++) {
				std::cout << "[" << index << "] : " << (*ite->second)[i] << std::endl;
			}
		i++;
	} //TODO

	for (size_t j = 0; j < checkers_.size(); j++) {
		checkers_[j](*this);
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
	params_[type] = param;
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
