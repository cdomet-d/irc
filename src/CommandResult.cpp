//HEADER

#include "CommandResult.hpp"

#include "CommandResult.hpp"

/* constructors & destructor */
CommandResult::CommandResult(void)
{
	//std::cout << "CommandResult default constructor called" << std::endl;
}

CommandResult::CommandResult(const CommandResult& obj)
{
	//std::cout << "CommandResult copy constructor called" << std::endl;
}

CommandResult::~CommandResult(void)
{
	//std::cout << "CommandResult destructor called" << std::endl;
}

/*operators*/
CommandResult&	CommandResult::operator=(const CommandResult& obj)
{
	//std::cout << "CommandResult copy assignment operator called" << std::endl;
	return (*this);
}

/*methods*/
CommandResult&	CommandResult::process(std::string& buffer)
{
	
}

std::string		CommandResult::getName(void)
{
	return (this->name);
}