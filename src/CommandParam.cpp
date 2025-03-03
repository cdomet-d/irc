//HEADER

#include "CommandParam.hpp"

/* constructors & destructor */
CommandParam::CommandParam(void)
{
	//std::cout << "CommandParam default constructor called" << std::endl;
}

CommandParam::CommandParam(std::vector<std::string> param, std::vector<void(*)()> checkers)
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


//nested class ------------------------------------------------


/* constructors & destructor */
CommandParam::ParamBuilder::ParamBuilder(void)
{
	//std::cout << "ParamBuilder default constructor called" << std::endl;
}

CommandParam::ParamBuilder::ParamBuilder(const ParamBuilder& obj)
{
	//std::cout << "ParamBuilder copy constructor called" << std::endl;
}

CommandParam::ParamBuilder::~ParamBuilder(void)
{
	//std::cout << "ParamBuilder destructor called" << std::endl;
}

/*operators*/
CommandParam::ParamBuilder&	CommandParam::ParamBuilder::operator=(const ParamBuilder& obj)
{
	//std::cout << "ParamBuilder copy assignment operator called" << std::endl;
	return (*this);
}

/*methods*/
CommandParam::ParamBuilder&	CommandParam::ParamBuilder::addChecker(void(*ft)())
{
	this->checkers.push_back(ft);
	return (*this);
}

CommandParam*	CommandParam::ParamBuilder::build()
{
	return (new CommandParam(this->param, this->checkers));
}
