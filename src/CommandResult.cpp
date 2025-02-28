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

/*nested class -----------------------------------*/


// /* constructors & destructor */
// CommandResult::test::test(void)
// {
// 	//std::cout << "CommandResult default constructor called" << std::endl;
// }

// CommandResult::test::test(const CommandResult::test& obj)
// {
// 	//std::cout << "CommandResult copy constructor called" << std::endl;
// }

// CommandResult::test::~test(void)
// {
// 	//std::cout << "CommandResult destructor called" << std::endl;
// }

// /*operators*/
// CommandResult::test&	CommandResult::test::operator=(const CommandResult::test& obj)
// {
// 	//std::cout << "CommandResult copy assignment operator called" << std::endl;
// 	return (*this);
// }
