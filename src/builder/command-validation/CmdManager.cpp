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

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */
CmdManager::CmdManager(void) {}

CmdManager::~CmdManager(void) {
	for (cmdMap::iterator it = commandList_.begin(); it != commandList_.end();
		 it++) {
		delete it->second;
	}
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */
void CmdManager::executeCm(CmdSpec &cm) {
std::cout << "in execute funcntion" << std::endl;
	if (cm.getValid())
		cm.getExecutor()(cm);
	cm.cleanAll();
}

void CmdManager::generateCmds() {
	log(CmdSpec::CmdBuilder()
			.Name("PASS")
			.Registration(0)
			.Parameters(password, new CmdParam())
			.addChecker(isRegistered)
			.addChecker(pwMatch)
			//.CmExecutor()
			.build());

	//on veut pas afficher ERR_NEEDMOREPARAMS si nickname est pas donné
	log(CmdSpec::CmdBuilder()
			.Name("NICK")
			.Registration(1)
			.Parameters(nickname, new CmdParam())
			.addChecker(validNick)
			// .CmExecutor()
			.build());

	log(CmdSpec::CmdBuilder()
			.Name("USER")
			.Registration(2)
			.Parameters(username, new CmdParam())
			.Parameters(hostname, new CmdParam())
			.Parameters(servername, new CmdParam())
			.Parameters(realname, new CmdParam())
			.addChecker(isRegistered)
			.addChecker(validUser)
			// .CmExecutor()
			.build());

	//meme si un channel est faux on fait ceux qui sont juste
	log(CmdSpec::CmdBuilder()
			.Name("JOIN")
			.Registration(3)
			.Parameters(channel, new CmdParam(false, ','))
			.Parameters(key, new CmdParam(true, ','))
			.addChecker(joinChanRequest)
			.CmExecutor(handleJoin)
			.build());

	//can have 0 params or 2
	log(CmdSpec::CmdBuilder()
			.Name("INVITE")
			.Registration(3)
			.Parameters(target, new CmdParam())
			.Parameters(channel, new CmdParam())
			.addChecker(validTarget)
			.addChecker(validChan)
			.addChecker(onChan)
			.addChecker(validInvite)
			.addChecker(hasChanPriv)
			// .CmExecutor()
			.build());

	//si un target est faux on fait pas ceux qui suivent
	log(CmdSpec::CmdBuilder()
			.Name("KICK")
			.Registration(3)
			.Parameters(channel, new CmdParam())
			.Parameters(target, new CmdParam(false, ','))
			.Parameters(message, new CmdParam(true, '\0'))
			.addChecker(validChan)
			.addChecker(onChan)
			.addChecker(hasChanPriv)
			.addChecker(validTarget)
			.addChecker(validKick)
			// .CmExecutor()
			.build());

	log(CmdSpec::CmdBuilder()
			.Name("MODE")
			.Registration(3)
			.Parameters(channel, new CmdParam())
			.Parameters(mode_, new CmdParam(true, ' '))
			.Parameters(modeArg, new CmdParam(true, ' '))
			.addChecker(validChan)
			.addChecker(hasChanPriv)
			.addChecker(validMode)
			// .addChecker(validArg) ?
			// .CmExecutor()
			.build());

	log(CmdSpec::CmdBuilder()
			.Name("PART")
			.Registration(3)
			.Parameters(channel, new CmdParam(false, ','))
			.Parameters(message, new CmdParam(true, '\0'))
			.addChecker(validChan)
			.addChecker(onChan)
			// .CmExecutor()
			.build());

	//we want ERR_NORECIPIENT not ERR_NEEDMOREPARAMS
	log(CmdSpec::CmdBuilder()
			.Name("PRIVMSG")
			.Registration(3)
			.Parameters(target, new CmdParam(false, ','))
			.Parameters(message, new CmdParam())
			.addChecker(validMess)
			.addChecker(validTarget)
			// .CmExecutor()
			.build());

	log(CmdSpec::CmdBuilder()
			.Name("QUIT")
			.Registration(0)
			.Parameters(message, new CmdParam(true, '\0'))
			// .CmExecutor()
			.build());

	log(CmdSpec::CmdBuilder()
			.Name("TOPIC")
			.Registration(3)
			.Parameters(channel, new CmdParam())
			.Parameters(topic_, new CmdParam(true, '\0'))
			.addChecker(validChan)
			.addChecker(onChan)
			.addChecker(hasChanPriv) //(only if mode +t is set)
			// .CmExecutor()
			.build());
}

void CmdManager::log(CmdSpec *cm) {
	commandList_[cm->getName()] = cm;
}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */
CmdSpec &CmdManager::getCmd(const std::string &cmName) {
	cmdMap::iterator it;

	it = commandList_.find(cmName);
	if (it == commandList_.end()) {
		throw CmdNotFoundException();
	}
	return (*it->second);
}

CmdManager &CmdManager::getManagerInstance() {
	static CmdManager instance;
	return (instance);
}