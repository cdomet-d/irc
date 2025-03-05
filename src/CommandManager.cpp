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
		cm.getExecutor()->execute(/*CommandParam*/);
}
void	CommandManager::generateCmds()
{
	//pass
	CommandSpec	*pass = CommandSpec::CommandBuilder()
									.Name("PASS")
									.Registration(0)
									.InputTokenizer(splitOnSpace)
									.MinParam(1) //(1)
									.Parameters(CommandParam::ParamBuilder() //password
												// .addChecker(pwMatch) (3)
												.build())
									// .IssuerChecks(isRegistered) //(2)
									// .CmExecutor()
									.build();

	log(pass);

	//nick
	CommandSpec	*nick = CommandSpec::CommandBuilder()
									.Name("NICK")
									.Registration(1)
									.InputTokenizer(splitOnSpace)
									.MinParam(0) //on veut pas afficher ERR_NEEDMOREPARAMS si nickname est pas donné
									.Parameters(CommandParam::ParamBuilder() //nickname
												// .addChecker(validNick)
												.build())
									// .CmExecutor()
									.build();

	log(nick);

	//user
	CommandSpec	*user = CommandSpec::CommandBuilder()
									.Name("USER")
									.Registration(2)
									// .InputTokenizer() split on space except if realname starts with ":"
									.MinParam(4) //(1)
									.Parameters(CommandParam::ParamBuilder() //username
												// .addChecker(validUser) //(3)
												.build())
									.Parameters(CommandParam::ParamBuilder() //0
												.build())
									.Parameters(CommandParam::ParamBuilder() //*
												.build())
									.Parameters(CommandParam::ParamBuilder() //realname
												.build())
									// .IssuerChecks(isRegistered) //(2)
									.build();

	log(user);

	//join
	CommandSpec	*join = CommandSpec::CommandBuilder()
									.Name("JOIN")
									.Registration(3)
									.InputTokenizer(splitOnComa)
									.MinParam(1) //(1)
									.Parameters(CommandParam::ParamBuilder() //channel(s)
												.addChecker(validChan) //(2)
												.addChecker(joinChanRequest) //(3)
												.build())
									// .Parameters(CommandParam::ParamBuilder() //key(s) (opt)
									// 			.build())
									.CmExecutor(new Join())//delete
									.build();

	log(join);

	//invite
	CommandSpec	*invite = CommandSpec::CommandBuilder()
									.Name("INVITE")
									.Registration(3)
									.InputTokenizer(splitOnSpace)
									.MinParam(2)//or 0 ? //(1) 
									.Parameters(CommandParam::ParamBuilder() ///nickname
												// .addChecker(validTarget) //(2)
												// .addChecker(validInvite) //(5)
												.build())
									.Parameters(CommandParam::ParamBuilder() ///channel
												.addChecker(validChan) //(3)
												.build())
									// .IssuerChecks(onChan) //(4)
									// .IssuerChecks(hasChanPriv) //(6)
									// .CmExecutor()
									.build();
								
	log(invite);
	
	//kick
	CommandSpec	*kick = CommandSpec::CommandBuilder()
									.Name("KICK")
									.Registration(3)
									.InputTokenizer(splitOnComa)
									.MinParam(2) //(1)
									.Parameters(CommandParam::ParamBuilder() //channel
												.addChecker(validChan) //(2)
												.build())
									.Parameters(CommandParam::ParamBuilder() //user(s)
												// .addChecker(validTarget) //(5)
												// .addChecker(validKick) //(6)
												.build())
									.Parameters(CommandParam::ParamBuilder() //comment (opt)
												.build())
									// .IssuerChecks(onChan) //(3)
									// .IssuerChecks(hasChanPriv) //(4)
									// .CmExecutor()
									.build();

	log(kick);

	//Mode
	CommandSpec	*mode = CommandSpec::CommandBuilder()
									.Name("MODE")
									.Registration(3)
									// .InputTokenizer()
									.MinParam(1) //(1)
									.Parameters(CommandParam::ParamBuilder() //channel
												.addChecker(validChan) //(2)
												.build())
									.Parameters(CommandParam::ParamBuilder() //modes + mode arg ?
												// .addChecker(validMode) //(2)
												.build())
									// .IssuerChecks(hasChanPriv) //(3)
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
									// .IssuerChecks(onChan) //(3)
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
									// .IssuerChecks(onChan)
									// .IssuerChecks(hasChanPriv) (only if mode +t is set)
									// .CmExecutor()
									.build();

	log(topic);
}

void	CommandManager::log(CommandSpec* cm)
{
	this->commandList[cm->getName()] = cm;
}