//HEADER

#include "CommandParam.hpp"

/* constructors & destructor */
CommandParam::CommandParam(void)
{
	//std::cout << "CommandParam default constructor called" << std::endl;
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

/*methods*/
CommandParam&	CommandParam::addChecker(void(*ft)())
{
	this->checkers.push_back(ft);
	return (*this);
}