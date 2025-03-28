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
				 std::vector< bool (*)(CmdSpec &) > checkers,
				 void (*cmExecutor)(CmdSpec &cmd))
	: server_(Server::GetServerInstance(0, "")), valid_(true), sender_(NULL),
	  name_(name), registrationStage_(registrationStage), params_(params),
	  checkers_(checkers), cmExecutor_(cmExecutor) {}

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
bool CmdSpec::checkRegistrationStage(void) {
	if (registrationStage_ > sender_->cliInfo.getRegistration()) {
		valid_ = false;
		if (name_ == "NICK")
			reply::send_(sender_->getFd(), "Please enter password\r\n");
		else if (name_ == "USER") {
			if (sender_->cliInfo.getRegistration() == 0)
				reply::send_(sender_->getFd(), "Please enter password\r\n");
			else
				reply::send_(sender_->getFd(), "Please enter nickname\r\n");
		} else if (name_ != "PASS")
			reply::send_(sender_->getFd(), ERR_NOTREGISTERED());
		return (false);
	}
	return (true);
}

bool CmdSpec::enoughParams() {
	if (name_ == "INVITE" && !(*this)[target_].size() &&
		!(*this)[channel_].size())
		return (true);
	for (size_t i = 0; i < params_.size(); i++) {
		CmdParam &innerParam = *params_[i].second;
		if (!innerParam.getOpt() && !innerParam.size()) {
			if (name_ == "NICK") {
				reply::send_((*sender_).getFd(), ERR_NONICKNAMEGIVEN());
			} else if (name_ == "PRIVMSG") {
				reply::send_((*sender_).getFd(), ERR_NOTEXTTOSEND());
			} else {
				reply::send_(
					(*sender_).getFd(),
					ERR_NEEDMOREPARAMS(sender_->cliInfo.getNick(), name_));
			}
			valid_ = false;
			return (false);
		}
	}
	return (true);
}

void CmdSpec::setParam(void) {
	for (size_t i = 0; i < params_.size() && i < sender_->mess.getSize(); i++) {
		try {
			(*params_[i].second).setOneParam(sender_->mess[i + 1]);
		} catch (const std::out_of_range &e) {}
	}
}

void CmdSpec::hasParamList(void) {
	for (size_t i = 0; i < params_.size(); i++) {
		CmdParam &innerParam = *params_[i].second;
		if (innerParam.getDelim()) {
			try {
				innerParam.setParamList(buffer_manip::vectorSplit(
					innerParam[0], innerParam.getDelim()));
			} catch (const std::out_of_range &e) {};
		}
	}
}

CmdSpec &CmdSpec::process(Client &sender) {

	setSender(sender);
	if (!checkRegistrationStage())
		return (*this);
	setParam();
	if (!enoughParams())
		return (*this);
	hasParamList();
	// displayParams();
	for (size_t i = 0; i < checkers_.size(); i++) {
		if (!checkers_[i](*this)) {
			valid_ = false;
			return (*this);
		}
	}
	return (*this);
}

void CmdSpec::cleanAll(void) {
	for (size_t i = 0; i < params_.size(); i++) {
		(*params_[i].second).clean();
	}
	valid_ = true;
}

static std::string enumToString(e_param color) {
	switch (color) {
	case 0:
		return "channel";
	case 1:
		return "hostname";
	case 2:
		return "key";
	case 3:
		return "message";
	case 4:
		return "flag";
	case 5:
		return "flagArg";
	case 6:
		return "nickname";
	case 7:
		return "password";
	case 8:
		return "realname";
	case 9:
		return "servername";
	case 10:
		return "target";
	case 11:
		return "topic";
	case 12:
		return "username";
	default:
		return "Unknown";
	}
}

void CmdSpec::displayParams(void) {
	std::cout << "Params in BuilderPattern :\n";
	for (paramMap::iterator i = params_.begin(); i != params_.end(); i++) {
		try {
			for (size_t index = 0; index < (*i->second).size(); index++) {
				std::cout << "param[" << enumToString(i->first) << "]"
						  << "[" << index << "] : " << (*i->second)[index]
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

Client &CmdSpec::getSender(void) const {
	return (*sender_);
}

const paramMap &CmdSpec::getParams(void) const {
	return (params_);
}

int CmdSpec::getRegistrationStage() const {
	return (registrationStage_);
}

/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */
void CmdSpec::setSender(Client &sender) {
	sender_ = &sender;
}

void CmdSpec::setValid(bool valid) {
	valid_ = valid;
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

CmdSpec::CmdBuilder &CmdSpec::CmdBuilder::addParam(e_param type,
												   CmdParam *param) {
	params_.push_back(std::make_pair(type, param));
	return (*this);
}

CmdSpec::CmdBuilder &CmdSpec::CmdBuilder::addChecker(bool (*ft)(CmdSpec &cmd)) {
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
