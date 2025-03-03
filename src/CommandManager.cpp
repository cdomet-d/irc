/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:14:35 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/03 17:16:12 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	std::map<std::string, CommandSpec*>::iterator	it;

	it = this->commandList.find(cmName);
	// if (it == commandList.end())
	// 	return ;
	return (*it->second); 
}

void	CommandManager::executeCm(CommandSpec& cm)
{
	if (!cm.getCancelled())
		cm.getExecutor()->execute();
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
									// .Parameters(CommandParam::ParamBuilder()
									// 			.addChecker(validKey)
									// 			.build())
									.MinParam(1)
									.CmExecutor(new Join())//delete
									.build();

	log(join); //register command
}

void	CommandManager::log(CommandSpec* cm)
{
	this->commandList[cm->getName()] = cm;
}