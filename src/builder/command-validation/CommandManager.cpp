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
		cm.getExecutor()(cm);
	cm.clean();
}
void	CommandManager::generateCmds()
{
	log(CommandSpec::CommandBuilder()
					.Name("PASS")
					.Registration(0)
					.Parameters(password, CommandParam::ParamBuilder().build())
					.addChecker(isRegistered)
					.addChecker(pwMatch)
					// .CmExecutor()
					.build());

	//on veut pas afficher ERR_NEEDMOREPARAMS si nickname est pas donné
	log(CommandSpec::CommandBuilder()
					.Name("NICK")
					.Registration(1)
					.Parameters(nickname, CommandParam::ParamBuilder().build())
					.addChecker(validNick)
					// .CmExecutor()
					.build());

	log(CommandSpec::CommandBuilder()
					.Name("USER")
					.Registration(2)
					.Parameters(username, CommandParam::ParamBuilder().build())
					.Parameters(hostname, CommandParam::ParamBuilder().build())
					.Parameters(servername, CommandParam::ParamBuilder().build())
					.Parameters(realname, CommandParam::ParamBuilder().build())
					.addChecker(isRegistered)
					.addChecker(validUser)
					// .CmExecutor()
					.build());

	log(CommandSpec::CommandBuilder()
					.Name("JOIN")
					.Registration(3)
					.Parameters(channel, CommandParam::ParamBuilder() //meme si un channel est faut on fait ceux qui sont juste
								.InputTokenizer(splitOnComa)
								.build())
					.Parameters(key, CommandParam::ParamBuilder()
								.isOpt(true)
								.InputTokenizer(splitOnComa)
								.build())
					.addChecker(joinChanRequest)
					// .CmExecutor()
					.build());

	//can have 0 params or 2
	log(CommandSpec::CommandBuilder()
					.Name("INVITE")
					.Registration(3)
					.Parameters(target, CommandParam::ParamBuilder().build())
					.Parameters(channel, CommandParam::ParamBuilder().build())
					.addChecker(validTarget)
					.addChecker(validChan)
					.addChecker(onChan)
					.addChecker(validInvite)
					.addChecker(hasChanPriv)
					// .CmExecutor()
					.build());
								
	log(CommandSpec::CommandBuilder()
					.Name("KICK")
					.Registration(3)
					.Parameters(channel, CommandParam::ParamBuilder().build())
					.Parameters(target, CommandParam::ParamBuilder() //si un target est faux on fait pas ceux qui suivent
								.InputTokenizer(splitOnComa)
								.build())
					.Parameters(message, CommandParam::ParamBuilder()
								.isOpt(true)
								.build())
					.addChecker(validChan)
					.addChecker(onChan)
					.addChecker(hasChanPriv)
					.addChecker(validTarget)
					.addChecker(validKick)
					// .CmExecutor()
					.build());

	log(CommandSpec::CommandBuilder()
					.Name("MODE")
					.Registration(3)
					.Parameters(channel, CommandParam::ParamBuilder().build())
					.Parameters(mode_, CommandParam::ParamBuilder()
								.isOpt(true)
								// .InputTokenizer()
								.build())
					.Parameters(modeArg, CommandParam::ParamBuilder()
								.isOpt(true)
								// .InputTokenizer()
								.build())
					.addChecker(validChan)
					.addChecker(hasChanPriv)
					.addChecker(validMode)
					// .CmExecutor()
					.build());

	log(CommandSpec::CommandBuilder()
					.Name("PART")
					.Registration(3)
					.Parameters(channel, CommandParam::ParamBuilder()
								.InputTokenizer(splitOnComa)
								.build())
					.Parameters(message, CommandParam::ParamBuilder()
								.isOpt(true)
								.build())
					.addChecker(validChan)
					.addChecker(onChan)
					// .CmExecutor()
					.build());

	//we want ERR_NORECIPIENT not ERR_NEEDMOREPARAMS
	log(CommandSpec::CommandBuilder()
					.Name("PRIVMSG")
					.Registration(3)
					.Parameters(target, CommandParam::ParamBuilder()
								.InputTokenizer(splitOnComa)
								.build())
					.Parameters(message, CommandParam::ParamBuilder().build())
					.addChecker(validMess)
					.addChecker(validTarget)
					// .CmExecutor()
					.build());

	log(CommandSpec::CommandBuilder()
					.Name("QUIT")
					.Registration(0)
					.Parameters(message, CommandParam::ParamBuilder()
								.isOpt(true)
								.build())
					// .CmExecutor()
					.build());

	log(CommandSpec::CommandBuilder()
					.Name("TOPIC")
					.Registration(3)
					.Parameters(channel, CommandParam::ParamBuilder().build())
					.Parameters(topic_, CommandParam::ParamBuilder()
								.isOpt(true)
								.build())
					.addChecker(validChan)
					.addChecker(onChan)
					.addChecker(hasChanPriv) //(only if mode +t is set)
					// .CmExecutor()
					.build());
}

void	CommandManager::log(CommandSpec* cm)
{
	this->commandList[cm->getName()] = cm;
}
