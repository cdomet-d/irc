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

/*methods*/
CommandResult&	CommandManager::getCmd(const std::string& cmName)
{
	std::map<std::string, CommandResult>::iterator	it;

	this->commandList.find(cmName);
	// if (it == commandList.end())
	// 	return (NULL);
	return (it->second); 
}

void	CommandManager::execute(CommandResult& cm)
{
	/*
		if (not cancelled)
			cm.getExecutor()
	*/
}

void	CommandManager::generateCmds()
{
	//join
	CommandSpec	join = CommandSpec()
							.Name("JOIN")
							.InputTokenizer(splitOnComa)
							.Registration(3)
							.build();

	log(join); //register command
}

void	CommandManager::log(CommandSpec& cm)
{
	this->commandList[cm.getCmdResult().getName()] = cm.getCmdResult();
}