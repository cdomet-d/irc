//HEADER

#include "CommandManager.hpp"

/* constructors & destructor */
CommandManager::CommandManager(void)
{
	//std::cout << "CommandManager default constructor called" << std::endl;
}

CommandManager::CommandManager(const CommandManager& obj)
{
	//std::cout << "CommandManager copy constructor called" << std::endl;
}

CommandManager::~CommandManager(void)
{
	//std::cout << "CommandManager destructor called" << std::endl;
}

/*operators*/
CommandManager&	CommandManager::operator=(const CommandManager& obj)
{
	//std::cout << "CommandManager copy assignment operator called" << std::endl;
	return (*this);
}


CommandResult&	CommandManager::getCmd(const std::string& cmName)
{

}

void	CommandManager::execute(CommandResult& cm)
{

}

void	CommandManager::generateCmds()
{
	//join
	CommandResult	join;

	this->commandList["JOIN"] = join;
}