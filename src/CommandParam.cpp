/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandParam.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:14:44 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/03 15:14:46 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandParam.hpp"

/* constructors & destructor */
CommandParam::CommandParam(void)
{
	//std::cout << "CommandParam default constructor called" << std::endl;
}

CommandParam::CommandParam(std::vector<std::string> param, std::vector<int(*)(std::string&)> checkers)
{
	this->param = param;
	this->checkers = checkers;
}

CommandParam::CommandParam(const CommandParam& obj)
{
	//std::cout << "CommandParam copy constructor called" << std::endl;
	*this = obj;
}

CommandParam::~CommandParam(void)
{
	//std::cout << "CommandParam destructor called" << std::endl;
}

/*operators*/
CommandParam&	CommandParam::operator=(const CommandParam& obj)
{
	//std::cout << "CommandParam copy assignment operator called" << std::endl;
	if (this != &obj)
	{
		this->param = obj.param;
		this->checkers = obj.checkers;
	}
	return (*this);
}

std::string&	CommandParam::operator[](unsigned int i)
{
	//add verif of index
	return (this->param[i]);
}

/*methods*/
std::vector<std::string>&	CommandParam::getParam(void)
{
	return (this->param);
}

size_t	CommandParam::getParamSize(void)
{
	return (this->param.size());
}

int	(*CommandParam::getChecker(unsigned int i))(std::string&)
{
	return (checkers[i]);
}

size_t	CommandParam::getCheckerSize(void)
{
	return (this->checkers.size());
}


//------------------------------ nested class ------------------------------------
/* constructors & destructor */
CommandParam::ParamBuilder::ParamBuilder(void)
{
	//std::cout << "ParamBuilder default constructor called" << std::endl;
}

CommandParam::ParamBuilder::ParamBuilder(const ParamBuilder& obj)
{
	//std::cout << "ParamBuilder copy constructor called" << std::endl;
	*this = obj;
}

CommandParam::ParamBuilder::~ParamBuilder(void)
{
	//std::cout << "ParamBuilder destructor called" << std::endl;
}

/*operators*/
CommandParam::ParamBuilder&	CommandParam::ParamBuilder::operator=(const ParamBuilder& obj)
{
	//std::cout << "ParamBuilder copy assignment operator called" << std::endl;
	if (this != &obj)
	{
		//
	}
	return (*this);
}

/*methods*/
CommandParam::ParamBuilder&	CommandParam::ParamBuilder::addChecker(int(*ft)(std::string&))
{
	this->checkers.push_back(ft);
	return (*this);
}

CommandParam*	CommandParam::ParamBuilder::build()
{
	return (new CommandParam(this->param, this->checkers));
}
