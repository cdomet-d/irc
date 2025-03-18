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
	// if (cm.getValid())
	// 	cm.getExecutor()(cm);
	cm.cleanAll();
}

void CmdManager::generateCmds() {
	log(CmdSpec::CmdBuilder()
			.Name("PASS")
			.Registration(0)
			.addParam(password_, new CmdParam())
			.addChecker(isRegistered)
			.addChecker(pwMatch)
			// .CmExecutor()
			.build());

	//on veut pas afficher ERR_NEEDMOREPARAMS si nickname est pas donné
	log(CmdSpec::CmdBuilder()
			.Name("NICK")
			.Registration(1)
			.addParam(nickname_, new CmdParam())
			.addChecker(validNick)
			// .CmExecutor()
			.build());

	log(CmdSpec::CmdBuilder()
			.Name("USER")
			.Registration(2)
			.addParam(username_, new CmdParam())
			.addParam(hostname_, new CmdParam())
			.addParam(servername_, new CmdParam())
			.addParam(realname_, new CmdParam())
			.addChecker(isRegistered)
			.addChecker(validUser)
			// .CmExecutor()
			.build());

	//meme si un channel est faux on fait ceux qui sont juste
	log(CmdSpec::CmdBuilder()
			.Name("JOIN")
			.Registration(3)
			.addParam(channel_, new CmdParam(false, ','))
			.addParam(key_, new CmdParam(true, ','))
			.addChecker(joinChanRequest)
			// .CmExecutor()
			.build());

	log(CmdSpec::CmdBuilder()
			.Name("INVITE")
			.Registration(3)
			.addParam(target_, new CmdParam())
			.addParam(channel_, new CmdParam())
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
			.addParam(channel_, new CmdParam())
			.addParam(target_, new CmdParam(false, ','))
			.addParam(message_, new CmdParam(true, '\0'))
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
			.addParam(channel_, new CmdParam())
			.addParam(mode_, new CmdParam(true, ' '))
			.addParam(modeArg_, new CmdParam(true, ' '))
			.addChecker(validChan)
			.addChecker(onChan) //TODO: verif if necessary
			.addChecker(hasChanPriv)
			.addChecker(validMode)
			// .addChecker(validArg) ?
			// .CmExecutor()
			.build());

	log(CmdSpec::CmdBuilder()
			.Name("PART")
			.Registration(3)
			.addParam(channel_, new CmdParam(false, ','))
			.addParam(message_, new CmdParam(true, '\0'))
			.addChecker(validChan)
			.addChecker(onChan)
			// .CmExecutor()
			.build());

	//we want ERR_NORECIPIENT not ERR_NEEDMOREPARAMS
	log(CmdSpec::CmdBuilder()
			.Name("PRIVMSG")
			.Registration(3)
			.addParam(target_, new CmdParam(false, ','))
			.addParam(message_, new CmdParam())
			.addChecker(validMess)
			.addChecker(validTarget)
			// .CmExecutor()
			.build());

	log(CmdSpec::CmdBuilder()
			.Name("QUIT")
			.Registration(0)
			.addParam(message_, new CmdParam(true, '\0'))
			// .CmExecutor()
			.build());

	log(CmdSpec::CmdBuilder()
			.Name("TOPIC")
			.Registration(3)
			.addParam(channel_, new CmdParam())
			.addParam(topic_, new CmdParam(true, '\0'))
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
CmdSpec &CmdManager::findCmd(const std::string &cmName) {
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