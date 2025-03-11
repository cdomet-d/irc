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

/* constructor & destructor */
CmdParam::CmdParam(std::vector<std::string> param, bool opt, \
	void(*inputTokenizer)(std::string& buffer, CmdParam& param))
{
	this->param_ = param;
	this->opt_ = opt;
	this->inputTokenizer_ = inputTokenizer;
}

CmdParam::~CmdParam(void)
{
	//std::cout << "CmdParam destructor called" << std::endl;
}

/*operators*/
std::string&	CmdParam::operator[](unsigned int i)
{
	//add verif of index
	return (this->param_[i]);
}

/*methods*/
std::vector<std::string>&	CmdParam::getParam(void)
{
	return (this->param_);
}

size_t	CmdParam::getParamSize(void)
{
	return (this->param_.size());
}


//------------------------------ nested class ------------------------------------
/* constructors & destructor */
CmdParam::ParamBuilder::ParamBuilder(void)
{
	//std::cout << "ParamBuilder default constructor called" << std::endl;
	this->opt_ = false;
	this->inputTokenizer_ = NULL;
}

CmdParam::ParamBuilder::~ParamBuilder(void)
{
	//std::cout << "ParamBuilder destructor called" << std::endl;
}

/*methods*/
CmdParam::ParamBuilder&	CmdParam::ParamBuilder::isOpt(bool opt)
{
	this->opt_ = opt;
	return (*this);
}

CmdParam::ParamBuilder&	CmdParam::ParamBuilder::InputTokenizer(void(*ft)(std::string& buffer, CmdParam& param))
{
	this->inputTokenizer_ = ft;
	return (*this);
}

CmdParam*	CmdParam::ParamBuilder::build()
{
	return (new CmdParam(this->param_, this->opt_, this->inputTokenizer_));
}
