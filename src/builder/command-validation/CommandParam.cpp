//HEADER

#include "CommandParam.hpp"

/* constructors & destructor */
CommandParam::CommandParam(void)
{
	//std::cout << "CommandParam default constructor called" << std::endl;
}

CommandParam::CommandParam(std::vector<std::string> param, std::vector<void(*)(std::string&)> checkers)
{
	param_ = param;
	checkers_ = checkers;
}

CommandParam::CommandParam(const CommandParam& rhs)
{
	//std::cout << "CommandParam copy constructor called" << std::endl;
	*this = rhs;
}

CommandParam::~CommandParam(void)
{
	//std::cout << "CommandParam destructor called" << std::endl;
}

/*operators*/
CommandParam&	CommandParam::operator=(const CommandParam& rhs)
{
	//std::cout << "CommandParam copy assignment operator called" << std::endl;
	if (this != &rhs)
	{
		param_ = rhs.param_;
		checkers_ = rhs.checkers_;
	}
	return (*this);
}

std::string&	CommandParam::operator[](unsigned int i)
{
	//add verif of index
	return (param_[i]);
}

//nested class ------------------------------------------------


/* constructors & destructor */
CommandParam::ParamBuilder::ParamBuilder(void)
{
	//std::cout << "ParamBuilder default constructor called" << std::endl;
}

CommandParam::ParamBuilder::ParamBuilder(const ParamBuilder& rhs)
{
	//std::cout << "ParamBuilder copy constructor called" << std::endl;
	*this = rhs;
}

CommandParam::ParamBuilder::~ParamBuilder(void)
{
	//std::cout << "ParamBuilder destructor called" << std::endl;
}

/*operators*/
CommandParam::ParamBuilder&	CommandParam::ParamBuilder::operator=(const ParamBuilder& rhs)
{
	//std::cout << "ParamBuilder copy assignment operator called" << std::endl;
	if (this != &rhs) {
		//
	}
	return (*this);
}

/*methods*/
CommandParam::ParamBuilder&	CommandParam::ParamBuilder::addChecker(void(*ft)(std::string&))
{
	checkers.push_back(ft);
	return (*this);
}

CommandParam*	CommandParam::ParamBuilder::build()
{
	return (new CommandParam(param, checkers));
}
