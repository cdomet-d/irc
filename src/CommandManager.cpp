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
	*this = obj;
}

CommandManager::~CommandManager(void)
{
	//std::cout << "CommandManager destructor called" << std::endl;
}

/*operators*/
CommandManager&	CommandManager::operator=(const CommandManager& obj)
{
	//std::cout << "CommandManager copy assignment operator called" << std::endl;
	if (this != &obj)
	{
		this->commandList = obj.commandList;
	}
	return (*this);
}

/*methods*/
CommandSpec&	CommandManager::getCmd(const std::string& cmName)
{
	std::map<std::string, CommandSpec>::iterator	it;

	it = this->commandList.find(cmName);
	// if (it == commandList.end())
	// 	return ;
	return (it->second); 
}

void	CommandManager::executeCm(CommandSpec& cm)
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
							.Registration(3)
							.InputTokenizer(splitOnComa)
							.Parameters(ParamGenerator()
										.addParam(CommandParam()
												.addChecker(validChan)
												.addChecker(joinChanRequest))
										.addParam(CommandParam()
												.addChecker(validKey)))
							.MinParam(1)
							.CmExecutor(new Join())//delete
							.build();

	log(join); //register command
}

void	CommandManager::log(CommandSpec& cm)
{
	this->commandList[cm.getName()] = cm;
}