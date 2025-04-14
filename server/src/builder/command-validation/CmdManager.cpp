/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::   */
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
CmdManager::CmdManager() {
	std::cout << "Cmd Manager instace created" << std::endl;
}

CmdManager::~CmdManager() {
	for (cmdMap::iterator it = commandList_.begin(); it != commandList_.end();
		 it++) {
		delete it->second;
	}
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */
bool CmdManager::executeCm(CmdSpec &cm) {
	if (cm.getValid()) {
		cm.getExecutor()(cm);
	}
	cm.cleanAll();
	if (cm.getName() == "QUIT")
		return (true);
	return (false);
}

void CmdManager::generateCmds() {
	log(CmdSpec::CmdBuilder()
			.Name("PASS")
			.Registration(0)
			.addParam(password_, new CmdParam())
			.addChecker(check::register_::stageDone)
			.addChecker(check::register_::isRegistered)
			.addChecker(check::enoughParams)
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
			.Registration(1)
			.addParam(username_, new CmdParam())
			.addParam(hostname_, new CmdParam())
			.addParam(servername_, new CmdParam())
			.addParam(realname_, new CmdParam())
			.addChecker(check::register_::stageDone)
			.addChecker(check::register_::isRegistered)
			.addChecker(check::enoughParams)
			.addChecker(check::user)
			.CmExecutor(user)
			.build());

	log(CmdSpec::CmdBuilder()
			.Name("JOIN")
			.Registration(3)
			.addParam(channel_, new CmdParam(false, true))
			.addParam(key_, new CmdParam(true, true))
			.addChecker(check::enoughParams)
			.addChecker(check::join)
			.CmExecutor(join)
			.build());

	log(CmdSpec::CmdBuilder()
			.Name("INVITE")
			.Registration(3)
			.addParam(target_, new CmdParam())
			.addParam(channel_, new CmdParam())
			.addChecker(check::enoughParams)
			.addChecker(check::chan)
			.addChecker(check::invite)
			.addChecker(check::chans_::isOp)
			.CmExecutor(invite)
			.build());

	log(CmdSpec::CmdBuilder()
			.Name("KICK")
			.Registration(3)
			.addParam(channel_, new CmdParam())
			.addParam(target_, new CmdParam(false, true))
			.addParam(message_, new CmdParam(true, false))
			.addChecker(check::enoughParams)
			.addChecker(check::chan)
			.addChecker(check::chans_::isOp)
			.addChecker(check::kick)
			.CmExecutor(kick)
			.build());

	log(CmdSpec::CmdBuilder()
			.Name("MODE")
			.Registration(3)
			.addParam(channel_, new CmdParam())
			.addParam(flag_, new CmdParam(true, true))
			.addParam(flagArg_, new CmdParam(true, true))
			.addChecker(check::enoughParams)
			.addChecker(check::chan)
			.addChecker(check::chans_::isOp)
			.addChecker(check::mode)
			.CmExecutor(mode)
			.build());

	log(CmdSpec::CmdBuilder()
			.Name("PART")
			.Registration(3)
			.addParam(channel_, new CmdParam(false, true))
			.addParam(message_, new CmdParam(true, false))
			.addChecker(check::enoughParams)
			.addChecker(check::part)
			.CmExecutor(part)
			.build());

	log(CmdSpec::CmdBuilder()
			.Name("PRIVMSG")
			.Registration(3)
			.addParam(target_, new CmdParam(false, true))
			.addParam(message_, new CmdParam())
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
			.addChecker(check::enoughParams)
			.addChecker(check::chan)
			.addChecker(check::chans_::isOp)
			.CmExecutor(topic)
			.build());

	log(CmdSpec::CmdBuilder()
			.Name("WHO")
			.Registration(3)
			.addParam(channel_, new CmdParam())
			.addParam(flag_, new CmdParam(true, false))
			.addChecker(check::enoughParams)
			.addChecker(check::chan)
			.CmExecutor(who)
			.build());

	log(CmdSpec::CmdBuilder()
			.Name("PING")
			.Registration(3)
			.addParam(message_, new CmdParam())
			.addChecker(check::enoughParams)
			.CmExecutor(ping)
			.build());
}

void CmdManager::log(CmdSpec *cm) {
	commandList_[cm->getName()] = cm;
}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */
CmdSpec &CmdManager::findCmd(std::string cmName) {
	cmdMap::iterator it;

	if (cmName.find_first_not_of("abcdefghijklmnopqrstuvwxyz")
		== std::string::npos)
		for (size_t i = 0; i < cmName.size(); i++)
			cmName[i] = std::toupper(cmName[i]);

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