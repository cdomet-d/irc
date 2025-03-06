//HEADER

#include "CommandManager.hpp"

/* constructors & destructor */
CommandManager::CommandManager(void)
{
	//std::cout << "CommandManager default constructor called" << std::endl;
}

CommandManager::CommandManager(const CommandManager& rhs)
{
	//std::cout << "CommandManager copy constructor called" << std::endl;
	*this = rhs;
}

CommandManager::~CommandManager(void)
{
	//std::cout << "CommandManager destructor called" << std::endl;
}

/*operators*/
CommandManager&	CommandManager::operator=(const CommandManager& rhs)
{
	//std::cout << "CommandManager copy assignment operator called" << std::endl;
	if (this != &rhs)
		this->commandList = rhs.commandList;
	return (*this);
}

/*methods*/
CommandSpec&	CommandManager::getCmd(const std::string& cmName)
{
	std::map<std::string, CommandSpec*>::iterator	it;

	it = this->commandList.find(cmName);
	// if (it == commandList.end())
	// 	return ;
	return (*it->second); 
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
	CommandSpec	*join = CommandSpec::CommandBuilder()
									.Name("JOIN")
									.Registration(3)
									.InputTokenizer(splitOnComa)
									.Parameters(CommandParam::ParamBuilder()
												.addChecker(validChan)
												.addChecker(joinChanRequest)
												.build())
									.Parameters(CommandParam::ParamBuilder()
												.addChecker(validKey)
												.build())
									.MinParam(1)
									.CmExecutor(new Join())//delete
									.build();

	log(join); //register command
}

void	CommandManager::log(CommandSpec* cm)
{
	this->commandList[cm->getName()] = cm;
}