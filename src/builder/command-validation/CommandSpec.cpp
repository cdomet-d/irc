/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandSpec.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:13:50 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/07 17:03:55 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandSpec.hpp"

/* constructor & destructor */
CommandSpec::CommandSpec(std::string name, int registrationStage, std::map<p_enum, std::vector<CommandParam*> > params, \
						std::vector<void(*)(CommandSpec&)> checkers, void(*cmExecutor)(CommandSpec& cmd))
{
	this->name_ = name;
	this->registrationStage_ = registrationStage;
	this->params_ = params;
	this->checkers_ = checkers;
	this->cmExecutor_ = cmExecutor;
	this->cancelled_ = false;
	this->sender_ = NULL;
}

CommandSpec::~CommandSpec(void)
{
	//std::cout << "CommandSpec destructor called" << std::endl;
}

/*methods*/
CommandSpec&	CommandSpec::process(std::string& buffer, Client& client)
{
	// std::cout << this->name << std::endl;
	// std::cout << "'" << buffer << "'" << std::endl;
	// std::cout << params.getParams().size() << std::endl;
	void(*tokenizer)(std::string& buffer, CommandParam& param)	= this->inputTokenizer_;
	
	if (client.getRegistration() != this->registrationStage_)
	{
		this->cancelled_ = true;
		return (*this);
	}
	for (size_t i = 0; i < params_.size(); i++)
		tokenizer(buffer, *params_[i]);
	//verif le nombre de param
	for (size_t i = 0; i < params_.size(); i++)
	{
		//est ce que j'applique un checker a la fois sur chaque param \
			ou tous les checkers sur chaque param a la fois? \
			dans quel ordre faire les checkers ? \
			si y a un checkers qui est pas bon est ce qu'on arrete ou on fait les autres checkers ?
		for (size_t j = 0; j < params_[i]->getCheckerSize(); j++)
		{
			int(*checker)(std::string&) = (*params_[i]).getChecker(j);
			for (size_t n = 0; n < params_[i]->getParamSize(); n++)
				checker((*params_[i])[n]);
		}
	}
	//s'ils ont tous ete supprimes mettre cancelled a true

	// for (size_t i = 0; i < params.size(); i++)
	// {
	// 	std::cout << "\nparam[" << i << "] : " << std::endl;
	// 	for (size_t j = 0; j < (*params[i]).getParamSize(); j++)
	// 		std::cout << (*params[i])[j] << std::endl;
	// }

	return (*this);
}

std::string	CommandSpec::getName(void)
{
	return (this->name_);
}

bool	CommandSpec::getCancelled(void)
{
	return (this->cancelled_);
}

void	(*CommandSpec::getExecutor(void))(CommandSpec& cmd)
{
	return (this->cmExecutor_);
}

/*----------------------------------- nested class -----------------------------------*/
/* constructors & destructor */
CommandSpec::CommandBuilder::CommandBuilder(void)
{
	//std::cout << "CommandBuilder default constructor called" << std::endl;
	this->name_ = "";
	this->registrationStage_ = 0;
	this->cmExecutor_ = NULL;
}

CommandSpec::CommandBuilder::CommandBuilder(const CommandBuilder& obj)
{
	//std::cout << "CommandBuilder copy constructor called" << std::endl;
	*this = obj;
}

CommandSpec::CommandBuilder::~CommandBuilder(void)
{
	//std::cout << "CommandBuilder destructor called" << std::endl;
}

/*operators*/
CommandSpec::CommandBuilder&	CommandSpec::CommandBuilder::operator=(const CommandBuilder& obj)
{
	//std::cout << "CommandBuilder copy assignment operator called" << std::endl;
	if (this != &obj)
	{
		//
	}
	return (*this);
}

/*methods*/
CommandSpec::CommandBuilder&	CommandSpec::CommandBuilder::Name(const std::string& name)
{
	this->name_ = name;
	return (*this);
}

CommandSpec::CommandBuilder&	CommandSpec::CommandBuilder::Registration(int stage)
{
	this->registrationStage_ = stage;
	return (*this);
}

CommandSpec::CommandBuilder&	CommandSpec::CommandBuilder::Parameters(p_enum type, CommandParam* param)
{
	this->params_[type].push_back(param);
	return (*this);
}

CommandSpec::CommandBuilder&	CommandSpec::CommandBuilder::addChecker(void(*ft)(CommandSpec& cmd))
{
	this->checkers_.push_back(ft);
	return (*this);
}

CommandSpec::CommandBuilder&	CommandSpec::CommandBuilder::CmExecutor(void(*ft)(CommandSpec& cmd))
{
	this->cmExecutor_ = ft;
	return (*this);
}

CommandSpec*	CommandSpec::CommandBuilder::build()
{
	return (new CommandSpec(name_, registrationStage_, params_, checkers_, cmExecutor_));
}
