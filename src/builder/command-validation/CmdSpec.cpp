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
	paramMap::iterator it;

	it = params_.find(type);
	//TODO: add secu if type not found
	// if (it == params_.end())
	// 	return (NULL);
	return (*it->second);
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */
CmdSpec &CmdSpec::process(std::vector< std::string > &buffer, Client &client) {
	(void)buffer;
	setSender(client);
	// std::cout << name << std::endl;
	// std::cout << "'" << buffer << "'" << std::endl;
	// std::cout << params.getParams().size() << std::endl;
	// void(*tokenizer)(std::string& buffer, CmdParam& param)	= inputTokenizer_;

	// if (client.getRegistration() != registrationStage_)
	// {
	// 	valid_ = false;
	// 	return (*this);
	// }
	// for (size_t i = 0; i < params_.size(); i++)
	// 	tokenizer(buffer, *params_[i]);
	// //verif le nombre de param
	// for (size_t i = 0; i < params_.size(); i++)
	// {
	// 	//est ce que j'applique un checker a la fois sur chaque param
	// 		ou tous les checkers sur chaque param a la fois?
	// 		dans quel ordre faire les checkers ?
	// 		si y a un checkers qui est pas bon est ce qu'on arrete ou on fait les autres checkers ?
	// 	for (size_t j = 0; j < params_[i]->getCheckerSize(); j++)
	// 	{
	// 		int(*checker)(std::string&) = (*params_[i]).getChecker(j);
	// 		for (size_t n = 0; n < params_[i]->getParamSize(); n++)
	// 			checker((*params_[i])[n]);
	// 	}
	// }
	//s'ils ont tous ete supprimes mettre cancelled a true

	// for (size_t i = 0; i < params.size(); i++)
	// {
	// 	std::cout << "\nparam[" << i << "] : " << std::endl;
	// 	for (size_t j = 0; j < (*params[i]).getParamSize(); j++)
	// 		std::cout << (*params[i])[j] << std::endl;
	// }

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
