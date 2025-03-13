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

Server &CmdSpec::server_ = Server::GetServerInstance(gPort, gPassword);

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
	for (size_t i = 0; i < params_.size(); i++) {
		if (params_[i].first == type)
			return ((*params_[i].second));
	}
	throw std::out_of_range("Param not found");
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */
bool CmdSpec::enoughParams() {
	if (name_ == "INVITE" && (*this)[target].getInnerParam().empty() &&
		(*this)[channel].getInnerParam().empty())
		return (true);
	if (name_ != "NICK" && name_ != "PRIVMSG") {
		for (size_t i = 0; i < params_.size(); i++) {
			CmdParam &param = *params_[i].second;
			if (!param.getOpt() && param.getInnerParam().empty()) {
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
	if (registrationStage_ > (*sender_).getRegistration()) {
		valid_ = false;
		if (name_ != "PASS" && name_ != "NICK" && name_ != "USER")
			std::cout << ERR_NOTREGISTERED;
		return (*this);
	}
	for (size_t i = 0; i < params_.size() && i < buffer.size(); i++) {
		(*params_[i].second).setOne(buffer[i]);
	}
	if (!enoughParams())
		return (*this);
	for (size_t index = 0; index < params_.size(); index++) {
		CmdParam &param = *params_[index].second;
		if (!param.getDelim().empty()) {
			try {
				param.setList(vectorSplit(param[0], param.getDelim()));
			} catch (const std::out_of_range &e) {};
		}
	}
	displayParams();
	for (size_t j = 0; j < checkers_.size(); j++) {
		checkers_[j](*this);
		if (!valid_)
			return (*this);
	}
	return (*this);
}

void CmdSpec::cleanAll(void) {
	for (size_t i = 0; i < params_.size(); i++) {
		(*params_[i].second).clean();
	}
}

static std::string enumToString(e_param color) {
	switch (color) {
	case 0:	return "channel";
	case 1:	return "hostname";
	case 2:	return "key";
	case 3:	return "message";
	case 4:	return "mode";
	case 5:	return "modeArg";
	case 6:	return "nickname";
	case 7:	return "password";
	case 8:	return "realname";
	case 9:	return "servername";
	case 10: return "target";
	case 11: return "topic";
	case 12: return "username";
	default: return "Unknown";
	}
}

void CmdSpec::displayParams(void) {
	for (paramMap::iterator itt = params_.begin(); itt != params_.end();
		 itt++) {
		try {
			for (size_t index = 0; index < (*itt->second).getSize();
				 index++) {
				std::cout << "param[" << enumToString(itt->first) << "]" 
						  << "[" << index << "] : " << (*itt->second)[index]
						  << std::endl;
			}
		} catch (const std::out_of_range &e) {
			std::cerr << e.what() << std::endl;
		}
		std::cout << "\n";
	}
}

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

const Client &CmdSpec::getSender(void) const {
	return (*sender_);
}

const paramMap& CmdSpec::getParams(void) const {
	return (params_);
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
