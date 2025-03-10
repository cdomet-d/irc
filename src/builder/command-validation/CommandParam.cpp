/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandParam.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:14:44 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/07 17:00:37 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandParam.hpp"

/* constructor & destructor */
CommandParam::CommandParam(std::vector<std::string> param, bool opt, \
	void(*inputTokenizer)(std::string& buffer, CommandParam& param))
{
	this->param_ = param;
	this->opt_ = opt;
	this->inputTokenizer_ = inputTokenizer;
}

CommandParam::~CommandParam(void)
{
	//std::cout << "CommandParam destructor called" << std::endl;
}

/*operators*/
std::string&	CommandParam::operator[](unsigned int i)
{
	//add verif of index
	return (this->param_[i]);
}

/*methods*/
std::vector<std::string>&	CommandParam::getParam(void)
{
	return (this->param_);
}

size_t	CommandParam::getParamSize(void)
{
	return (this->param_.size());
}


//------------------------------ nested class ------------------------------------
/* constructors & destructor */
CommandParam::ParamBuilder::ParamBuilder(void)
{
	//std::cout << "ParamBuilder default constructor called" << std::endl;
	this->opt_ = false;
	this->inputTokenizer_ = NULL;
}

CommandParam::ParamBuilder::~ParamBuilder(void)
{
	//std::cout << "ParamBuilder destructor called" << std::endl;
}

/*methods*/
CommandParam::ParamBuilder&	CommandParam::ParamBuilder::isOpt(bool opt)
{
	this->opt_ = opt;
	return (*this);
}

CommandParam::ParamBuilder&	CommandParam::ParamBuilder::InputTokenizer(void(*ft)(std::string& buffer, CommandParam& param))
{
	this->inputTokenizer_ = ft;
	return (*this);
}

CommandParam*	CommandParam::ParamBuilder::build()
{
	return (new CommandParam(this->param_, this->opt_, this->inputTokenizer_));
}
