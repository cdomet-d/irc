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

/* ------------------------------ nested class ---------------------------------------- */

/* constructors & destructor */
CommandResult::CommandSpec::CommandSpec(void)
{
	//std::cout << "CommandSpec default constructor called" << std::endl;
}

CommandResult::CommandSpec::CommandSpec(const CommandSpec& obj)
{
	//std::cout << "CommandSpec copy constructor called" << std::endl;
}

CommandResult::CommandSpec::~CommandSpec(void)
{
	//std::cout << "CommandSpec destructor called" << std::endl;
}

/*operators*/
CommandResult::CommandSpec&	CommandResult::CommandSpec::operator=(const CommandResult::CommandSpec& obj)
{
	//std::cout << "CommandSpec copy assignment operator called" << std::endl;
	return (*this);
}

