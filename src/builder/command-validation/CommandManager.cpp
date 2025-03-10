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
}
void	CommandManager::generateCmds()
{
	//pass
	CommandSpec	*pass = CommandSpec::CommandBuilder()
									.Name("PASS")
									.Registration(0)
									.Parameters(password, CommandParam::ParamBuilder().build())
									// .addChecker(isRegistered) //(2)
									// .addChecker(pwMatch) (3)
									// .CmExecutor()
									.build();

	log(pass);

	//nick
	//on veut pas afficher ERR_NEEDMOREPARAMS si nickname est pas donné
	CommandSpec	*nick = CommandSpec::CommandBuilder()
									.Name("NICK")
									.Registration(1)
									.Parameters(nickname, CommandParam::ParamBuilder().build())
									// .addChecker(validNick)
									// .CmExecutor()
									.build();

	log(nick);

	//user
	CommandSpec	*user = CommandSpec::CommandBuilder()
									.Name("USER")
									.Registration(2)
									.Parameters(username, CommandParam::ParamBuilder().build())
									.Parameters(hostname, CommandParam::ParamBuilder().build())
									.Parameters(servername, CommandParam::ParamBuilder().build())
									.Parameters(realname, CommandParam::ParamBuilder().build())
									// .addChecker(isRegistered) //(2)
									// .addChecker(validUser) //(3)
									// .CmExecutor()
									.build();

	log(user);

	//join
	CommandSpec	*join = CommandSpec::CommandBuilder()
									.Name("JOIN")
									.Registration(3)
									.Parameters(channel, CommandParam::ParamBuilder() //meme si un channel est faut on fait cexu qui sont juste
												.InputTokenizer(splitOnComa)
												.build())
									.Parameters(key, CommandParam::ParamBuilder()
												.isOpt(true)
												.InputTokenizer(splitOnComa)
												.build())
									// .addChecker(validChan) //(2)
									// .addChecker(joinChanRequest) //(3)
									// .CmExecutor()
									.build();

	log(join);

	//invite
	//can have 0 params or 2
	CommandSpec	*invite = CommandSpec::CommandBuilder()
									.Name("INVITE")
									.Registration(3)
									.Parameters(target, CommandParam::ParamBuilder().build())
									.Parameters(channel, CommandParam::ParamBuilder().build())
									// .addChecker(validTarget) //(2)
									// .addChecker(validChan) //(3)
									// .addChecker(onChan) //(4)
									// .addChecker(validInvite) //(5)
									// .addChecker(hasChanPriv) //(6)
									// .CmExecutor()
									.build();
								
	log(invite);
	
	//kick
	CommandSpec	*kick = CommandSpec::CommandBuilder()
									.Name("KICK")
									.Registration(3)
									.Parameters(channel, CommandParam::ParamBuilder().build())
									.Parameters(target, CommandParam::ParamBuilder() //si un target est faux on fait pas les ceux qui suivent
												.InputTokenizer(splitOnComa)
												.build())
									.Parameters(comment, CommandParam::ParamBuilder()
												.isOpt(true)
												.build())
									// .addChecker(validChan) //(2)
									// .addChecker(onChan) //(3)
									// .addChecker(hasChanPriv) //(4)
									// .addChecker(validTarget) //(5)
									// .addChecker(validKick) //(6)
									// .CmExecutor()
									.build();

	log(kick);

	//Mode
	CommandSpec	*mode = CommandSpec::CommandBuilder()
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
									// .addChecker(validChan) //(2)
									// .addChecker(hasChanPriv) //(3)
									// .addChecker(validMode) //(4)
									// .CmExecutor()
									.build();

	log(mode);

	//part
	CommandSpec	*part = CommandSpec::CommandBuilder()
									.Name("PART")
									.Registration(3)
									.InputTokenizer(splitOnComa)
									.MinParam(1) //(1)
									.Parameters(CommandParam::ParamBuilder() //channel(s)
												.addChecker(validChan) //(2)
												.build())
									.Parameters(CommandParam::ParamBuilder() //reason (opt)
												.build())
									// .addChecker(onChan) //(3)
									// .CmExecutor()
									.build();

	log(part);

	//privmsg
	CommandSpec	*privmsg = CommandSpec::CommandBuilder()
									.Name("PRIVMSG")
									.Registration(3)
									.InputTokenizer(splitOnSpace)
									.MinParam(0) //we want ERR_NORECIPIENT not ERR_NEEDMOREPARAMS
									.Parameters(CommandParam::ParamBuilder() //receiver(s)
												// .addChecker(validTarget) (2)
												.build())
									.Parameters(CommandParam::ParamBuilder() //text to be sent
												// .addChecker(validMess) (1)
												.build())
									// .CmExecutor()
									.build();

	log(privmsg);

	//quit
	CommandSpec	*quit = CommandSpec::CommandBuilder()
									.Name("QUIT")
									.Registration(0)
									// .InputTokenizer() //if ":" pas de split else splitOnSpace
									.MinParam(0)
									.Parameters(CommandParam::ParamBuilder() //quit message (opt)
												.build())
									// .CmExecutor()
									.build();

	log(quit);

	//topic
	CommandSpec	*topic = CommandSpec::CommandBuilder()
									.Name("TOPIC")
									.Registration(3)
									.InputTokenizer(splitOnSpace)
									.MinParam(1) //(1)
									.Parameters(CommandParam::ParamBuilder() //channel
												.addChecker(validChan) //(2)
												.build())
									.Parameters(CommandParam::ParamBuilder() //topic (opt)
												.build())
									// .addChecker(onChan)
									// .addChecker(hasChanPriv) (only if mode +t is set)
									// .CmExecutor()
									.build();

	log(topic);
}

void	CommandManager::log(CommandSpec* cm)
{
	this->commandList[cm->getName()] = cm;
}