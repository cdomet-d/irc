/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:43:39 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/18 17:00:29 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdSpec.hpp"
#include "Server.hpp"
#include <cstdlib>
#include <sstream>

void executeO(std::string flag, std::string param, Channel *curChan)
{
	Client *target;

	//find instance of target
	for (clientMapIt targetIt = curChan->getCliInChan().begin();
		 targetIt != curChan->getCliInChan().end(); ++targetIt) {
		if (targetIt->second->cliInfo.getNick() == param) {
			target = targetIt->second;
			break;
		}
	}
	if (flag == "+o")
		curChan->getOpCli().insert(
			std::pair< int, Client * >(target->getFd(), target));
	if (flag == "-o")
		curChan->getOpCli().erase(target->getFd());
}

void executeI(std::string flag, std::string param, Channel *curChan)
{
	(void)param;

	if (flag == "+i" && curChan->getInviteOnly() == false) {
		curChan->setInviteOnly(true);
		curChan->setModes();
	}
	if (flag == "-i" && curChan->getInviteOnly() == true) {
		curChan->setInviteOnly(false);
		curChan->setModes();
	}
}
void executeT(std::string flag, std::string param, Channel *curChan)
{
	(void)param;

	if (flag == "+t" && curChan->getTopicRestrict() == false) {
		curChan->setTopicRestrict(true);
		curChan->setModes();
	}
	if (flag == "-t" && curChan->getTopicRestrict() == true) {
		curChan->setTopicRestrict(false);
		curChan->setModes();
	}
}

void executeK(std::string flag, std::string param, Channel *curChan)
{
	if (flag == "+k") {
		curChan->setPassword(param);
		curChan->setIsPassMatch(true);
		curChan->setModes();
	}

	if (flag == "-k" && curChan->getIsPassMatch() == true) {
		curChan->setPassword("");
		curChan->setIsPassMatch(false);
		curChan->setModes();
	}
}

void executeL(std::string flag, std::string param, Channel *curChan)
{
	if (flag == "+l") {
		curChan->setMaxCli(atoi(param.c_str()));
		curChan->setIsPassMatch(true);
		curChan->setModes();
	}

	if (flag == "-l" && curChan->getMaxCli() == 0) {
		curChan->setMaxCli(0);
		curChan->setIsPassMatch(false);
		curChan->setModes();
	}
}

int findFlagLevel(std::string level)
{
	std::string flag[5] = {"o", "i", "t", "k", "l"};
	for (int i = 0; i < 5; i++) {
		if (level.find(flag[i]) != std::string::npos)
			return (i);
	}
	return (-1);
}

void executeFlag(std::string flag, std::string param, Channel *curChan)
{
	modesFunc flagExecutor[5] = {&executeO, &executeI, &executeT, &executeK,
								 &executeL};
	int flagLevel = findFlagLevel(flag);

	if (flagLevel != -1)
		flagExecutor[flagLevel](flag, param, curChan);
	else
		logLevel(DEBUG, "Invalid flag");
}

Channel *findCurChan(std::string chanName)
{
	static Server &server = Server::GetServerInstance(0, "");
	channelMapIt curChanIt = server.getAllChan().find(chanName);

	return (curChanIt->second);
}

//the modes of a channel need to be empty if no moe is activated and +<modes> if any
//TODO the first params will be the nam of the channel
void handleMode(CmdSpec &cmd)
{
	logLevel(DEBUG, "-----handleMode-----");
	Client *sender = &cmd.getSender();
	Channel *curChan = findCurChan(cmd[channel][0]);
	std::string newModes;
	std::string newMaxCli = "";

	if (!cmd[mode_].getSize()) {
		std::cout << "hEREEE!" << std::endl;
		sendReply(sender->getFd(),
				  RPL_UMODEIS(sender->cliInfo.getNick(), curChan->getModes()));
		return;
	}
	for (size_t nbFlag = 0; nbFlag < cmd[mode_].getSize(); ++nbFlag) {
		if (cmd[mode_][nbFlag] == "+l")
			newMaxCli = cmd[modeArg][nbFlag];
		executeFlag(cmd[mode_][nbFlag], cmd[modeArg][nbFlag], curChan);
		newModes.append(cmd[mode_][nbFlag]);
	}
	newModes.append(newMaxCli);
	sendMessageChannel(curChan->getCliInChan(),
					   RPL_CHANNELMODEIS(sender->cliInfo.getNick(),
										 curChan->getName(), newModes));
}
