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
#include "CmdExecution.hpp"
#include "Server.hpp"
#include "typedef.hpp"
#include "validator.hpp"

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */
CmdManager::CmdManager(void) {
	std::cout << "Cmd Manager instace created" << std::endl;
}

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
	if (cm.getValid()) {
		cm.getExecutor()(cm);
	}
	cm.cleanAll();
}

void CmdManager::generateCmds() {
	log(CmdSpec::CmdBuilder()
			.Name("PASS")
			.Registration(0)
			.addParam(password_, new CmdParam())
			.addChecker(check::register_::stageDone)
			.addChecker(check::register_::isRegistered)
			.addChecker(check::register_::pwMatch)
			.CmExecutor(pass)
			.build());

	log(CmdSpec::CmdBuilder()
			.Name("NICK")
			.Registration(1)
			.addParam(nickname_, new CmdParam())
			.addChecker(check::register_::stageDone)
			.addChecker(check::nick)
			.CmExecutor(nick)
			.build());

	log(CmdSpec::CmdBuilder()
			.Name("USER")
			.Registration(2)
			.addParam(username_, new CmdParam())
			.addParam(hostname_, new CmdParam())
			.addParam(servername_, new CmdParam())
			.addParam(realname_, new CmdParam())
			.addChecker(check::register_::isRegistered)
			.addChecker(check::user)
			.CmExecutor(user)
			.build());

	log(CmdSpec::CmdBuilder()
			.Name("JOIN")
			.Registration(3)
			.addParam(channel_, new CmdParam(false, true))
			.addParam(key_, new CmdParam(true, true))
			.addChecker(check::join)
			.CmExecutor(join)
			.build());

	log(CmdSpec::CmdBuilder()
			.Name("INVITE")
			.Registration(3)
			.addParam(target_, new CmdParam()) //can be empty
			.addParam(channel_, new CmdParam()) //can be empty
			.addChecker(check::target)
			.addChecker(check::chan)
			.addChecker(check::chans_::isOnChan)
			.addChecker(check::invite)
			.addChecker(check::chans_::hasChanAuthorisations)
			.CmExecutor(invite)
			.build());

	log(CmdSpec::CmdBuilder()
			.Name("KICK")
			.Registration(3)
			.addParam(channel_, new CmdParam())
			.addParam(target_, new CmdParam(false, true))
			.addParam(message_, new CmdParam(true, false))
			.addChecker(check::chan)
			.addChecker(check::chans_::isOnChan)
			.addChecker(check::chans_::hasChanAuthorisations)
			.addChecker(check::target)
			.addChecker(check::kick)
			.CmExecutor(kick)
			.build());

	log(CmdSpec::CmdBuilder()
			.Name("MODE")
			.Registration(3)
			.addParam(channel_, new CmdParam())
			.addParam(flag_, new CmdParam(true, true))
			.addParam(flagArg_, new CmdParam(true, true))
			.addChecker(check::chan)
			.addChecker(check::chans_::isOnChan)
			.addChecker(check::chans_::hasChanAuthorisations)
			.addChecker(check::mode)
			.CmExecutor(mode)
			.build());

	log(CmdSpec::CmdBuilder()
			.Name("PART")
			.Registration(3)
			.addParam(channel_, new CmdParam(false, true))
			.addParam(message_, new CmdParam(true, false))
			.addChecker(check::chan)
			.addChecker(check::chans_::isOnChan)
			.CmExecutor(part)
			.build());

	log(CmdSpec::CmdBuilder()
			.Name("PRIVMSG")
			.Registration(3)
			.addParam(target_, new CmdParam(false, true))
			.addParam(message_, new CmdParam())
			//TODO: regarder si le target commence par un #, si oui faire validChan et isOnChan si non faire validTarget
			.addChecker(check::mess)
			.CmExecutor(privmsg)
			.build());

	log(CmdSpec::CmdBuilder()
			.Name("QUIT")
			.Registration(0)
			.addParam(message_, new CmdParam(true, false))
			.CmExecutor(quit)
			.build());

	log(CmdSpec::CmdBuilder()
			.Name("TOPIC")
			.Registration(3)
			.addParam(channel_, new CmdParam())
			.addParam(topic_, new CmdParam(true, false))
			.addChecker(check::chan)
			.addChecker(check::chans_::isOnChan)
			.addChecker(check::chans_::hasChanAuthorisations)
			.CmExecutor(topic)
			.build());

	log(CmdSpec::CmdBuilder()
			.Name("WHO")
			.Registration(3)
			.addParam(channel_, new CmdParam())
			.addParam(flag_, new CmdParam(true, false))
			.addChecker(check::chan)
			.addChecker(check::chans_::isOnChan)
			//TODO: add checker for flag "o"
			.CmExecutor(who)
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