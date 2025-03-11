/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:14:35 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/03 17:16:12 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdManager.hpp"

/* constructors & destructor */
CmdManager::CmdManager(void)
{
	//std::cout << "CmdManager default constructor called" << std::endl;
}

CmdManager::CmdManager(const CmdManager& obj)
{
	//std::cout << "CmdManager copy constructor called" << std::endl;
	*this = obj;
}

CmdManager::~CmdManager(void)
{
	//std::cout << "CmdManager destructor called" << std::endl;
}

/*operators*/
CmdManager&	CmdManager::operator=(const CmdManager& obj)
{
	//std::cout << "CmdManager copy assignment operator called" << std::endl;
	if (this != &obj)
	{
		this->commandList = obj.commandList;
	}
	return (*this);
}

/*methods*/
CmdSpec&	CmdManager::getCmd(const std::string& cmName)
{
	std::map<std::string, CmdSpec*>::iterator	it;

	it = this->commandList.find(cmName);
	// if (it == commandList.end())
	// 	return ;
	return (*it->second); 
}

void	CmdManager::executeCm(CmdSpec& cm)
{
	if (!cm.getCancelled())
		cm.getExecutor()(cm);
	cm.clean();
}
void	CmdManager::generateCmds()
{
	log(CmdSpec::CommandBuilder()
					.Name("PASS")
					.Registration(0)
					.Parameters(password, CmdParam::ParamBuilder().build())
					.addChecker(isRegistered)
					.addChecker(pwMatch)
					// .CmExecutor()
					.build());

	//on veut pas afficher ERR_NEEDMOREPARAMS si nickname est pas donné
	log(CmdSpec::CommandBuilder()
					.Name("NICK")
					.Registration(1)
					.Parameters(nickname, CmdParam::ParamBuilder().build())
					.addChecker(validNick)
					// .CmExecutor()
					.build());

	log(CmdSpec::CommandBuilder()
					.Name("USER")
					.Registration(2)
					.Parameters(username, CmdParam::ParamBuilder().build())
					.Parameters(hostname, CmdParam::ParamBuilder().build())
					.Parameters(servername, CmdParam::ParamBuilder().build())
					.Parameters(realname, CmdParam::ParamBuilder().build())
					.addChecker(isRegistered)
					.addChecker(validUser)
					// .CmExecutor()
					.build());

	log(CmdSpec::CommandBuilder()
					.Name("JOIN")
					.Registration(3)
					.Parameters(channel, CmdParam::ParamBuilder() //meme si un channel est faut on fait ceux qui sont juste
								.setDelim(",")
								.build())
					.Parameters(key, CmdParam::ParamBuilder()
								.isOpt(true)
								.setDelim(",")
								.build())
					.addChecker(joinChanRequest)
					// .CmExecutor()
					.build());

	//can have 0 params or 2
	log(CmdSpec::CommandBuilder()
					.Name("INVITE")
					.Registration(3)
					.Parameters(target, CmdParam::ParamBuilder().build())
					.Parameters(channel, CmdParam::ParamBuilder().build())
					.addChecker(validTarget)
					.addChecker(validChan)
					.addChecker(onChan)
					.addChecker(validInvite)
					.addChecker(hasChanPriv)
					// .CmExecutor()
					.build());
								
	log(CmdSpec::CommandBuilder()
					.Name("KICK")
					.Registration(3)
					.Parameters(channel, CmdParam::ParamBuilder().build())
					.Parameters(target, CmdParam::ParamBuilder() //si un target est faux on fait pas ceux qui suivent
								.setDelim(",")
								.build())
					.Parameters(message, CmdParam::ParamBuilder()
								.isOpt(true)
								.build())
					.addChecker(validChan)
					.addChecker(onChan)
					.addChecker(hasChanPriv)
					.addChecker(validTarget)
					.addChecker(validKick)
					// .CmExecutor()
					.build());

	log(CmdSpec::CommandBuilder()
					.Name("MODE")
					.Registration(3)
					.Parameters(channel, CmdParam::ParamBuilder().build())
					.Parameters(mode_, CmdParam::ParamBuilder()
								.isOpt(true)
								.build())
					.Parameters(modeArg, CmdParam::ParamBuilder()
								.isOpt(true)
								.build())
					.addChecker(validChan)
					.addChecker(hasChanPriv)
					.addChecker(validMode)
					// .CmExecutor()
					.build());

	log(CmdSpec::CommandBuilder()
					.Name("PART")
					.Registration(3)
					.Parameters(channel, CmdParam::ParamBuilder()
								.setDelim(",")
								.build())
					.Parameters(message, CmdParam::ParamBuilder()
								.isOpt(true)
								.build())
					.addChecker(validChan)
					.addChecker(onChan)
					// .CmExecutor()
					.build());

	//we want ERR_NORECIPIENT not ERR_NEEDMOREPARAMS
	log(CmdSpec::CommandBuilder()
					.Name("PRIVMSG")
					.Registration(3)
					.Parameters(target, CmdParam::ParamBuilder()
								.setDelim(",")
								.build())
					.Parameters(message, CmdParam::ParamBuilder().build())
					.addChecker(validMess)
					.addChecker(validTarget)
					// .CmExecutor()
					.build());

	log(CmdSpec::CommandBuilder()
					.Name("QUIT")
					.Registration(0)
					.Parameters(message, CmdParam::ParamBuilder()
								.isOpt(true)
								.build())
					// .CmExecutor()
					.build());

	log(CmdSpec::CommandBuilder()
					.Name("TOPIC")
					.Registration(3)
					.Parameters(channel, CmdParam::ParamBuilder().build())
					.Parameters(topic_, CmdParam::ParamBuilder()
								.isOpt(true)
								.build())
					.addChecker(validChan)
					.addChecker(onChan)
					.addChecker(hasChanPriv) //(only if mode +t is set)
					// .CmExecutor()
					.build());
}

void	CmdManager::log(CmdSpec* cm)
{
	this->commandList[cm->getName()] = cm;
}
