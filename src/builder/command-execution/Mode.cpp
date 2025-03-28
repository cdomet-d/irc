/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:43:39 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/28 15:23:14 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Server.hpp"
#include <cerrno>
#include <cstdlib>
#include <limits>

//TODO : do we remove a ope if it's the only OP left of the channel
void executeO(std::string flag, std::string param, Channel &curChan) {
	Client *targetCli;

	//find instance of target
	for (clientMapIt targetIt = curChan.getCliInChan().begin();
		 targetIt != curChan.getCliInChan().end(); ++targetIt) {
		if (targetIt->second->cliInfo.getNick() == param) {
			targetCli = targetIt->second;
			break;
		}
	}
	if (flag == "+o") {
		curChan.addCli(OPCLI, targetCli); 
		reply::send_(targetCli->getFd(), RPL_CHANOPE(targetCli->cliInfo.getNick(), curChan.getName()));
	}
	if (flag == "-o") {
		curChan.removeCli(OPCLI, targetCli->getFd());
		reply::send_(targetCli->getFd(), RPL_CHANOPENOPE(targetCli->cliInfo.getNick(), curChan.getName()));

	}
}

void executeI(std::string flag, std::string param, Channel &curChan) {
	(void)param;

	if (flag == "+i" && curChan.getInviteOnly() == false) {
		curChan.setInviteOnly(true);
		curChan.setModes();
	}
	if (flag == "-i" && curChan.getInviteOnly() == true) {
		std::cout << "we here captain" << std::endl;
		curChan.setInviteOnly(false);
		curChan.setModes();
	}
}
void executeT(std::string flag, std::string param, Channel &curChan) {
	(void)param;

	if (flag == "+t" && curChan.getTopicRestrict() == false) {
		curChan.setTopicRestrict(true);
		curChan.setModes();
	}
	if (flag == "-t" && curChan.getTopicRestrict() == true) {
		curChan.setTopicRestrict(false);
		curChan.setModes();
	}
}

void executeK(std::string flag, std::string param, Channel &curChan) {
	if (flag == "+k") {
		curChan.setPassword(param);
		curChan.setIsPassMatch(true);
		curChan.setModes();
	}

	if (flag == "-k" && curChan.getIsPassMatch() == true) {
		curChan.setPassword("");
		curChan.setIsPassMatch(false);
		curChan.setModes();
	}
}

void executeL(std::string flag, std::string param, Channel &curChan) {
	if (flag == "+l") {
		char *endptr;
		errno = 0;
		double result = strtod(param.c_str(), &endptr);

		//if err of strtod, the maxCli of the channel will be set to the maxCi of the server so 50
		if (errno == ERANGE || *endptr != '\0' || result < 0 ||
			result > std::numeric_limits< int >::max()) {
			curChan.setMaxCli(50);
			curChan.setModes();
		} else {
			curChan.setMaxCli(static_cast< int >(result));
			curChan.setModes();
		}
	}
	if (flag == "-l" && curChan.getMaxCli() == 0) {
		curChan.setMaxCli(0);
		curChan.setModes();
	}
}

int findFlagLevel(std::string level) {
	std::string flag[5] = {"o", "i", "t", "k", "l"};
	for (int i = 0; i < 5; i++) {
		if (level.find(flag[i]) != std::string::npos)
			return (i);
	}
	return (-1);
}

void executeFlag(std::string flag, std::string param, Channel &curChan) {
	modesFunc flagExecutor[5] = {&executeO, &executeI, &executeT, &executeK,
								 &executeL};
	int flagLevel = findFlagLevel(flag);

	if (flagLevel != -1)
		flagExecutor[flagLevel](flag, param, curChan);
	else
		reply::log(reply::DEBUG, "Invalid flag");
}

Channel &findCurChan(std::string chanName) {
	static Server &server = Server::GetServerInstance(0, "");
	channelMapIt curChanIt = server.getAllChan().find(chanName);

	return (*curChanIt->second);
}

//the modes of a channel need to be empty if no moe is activated and +<modes> if any
void mode(CmdSpec &cmd) {
	Client *sender = &cmd.getSender();
	Channel &curChan = findCurChan(cmd[channel_][0]);
	std::string newModes;
	std::string newMaxCli = "";

	if (!cmd[flag_].size()) {
		reply::send_(sender->getFd(),
				  RPL_UMODEIS(sender->cliInfo.getNick(), curChan.getModes()));
		return;
	}
	for (size_t nbFlag = 0; nbFlag < cmd[flag_].size(); ++nbFlag) {
	std::cout << "cmd[flag_][nbFlag] = " << cmd[flag_][nbFlag] << std::endl << "cmd[flagArg_][nbFlag] = " << cmd[flagArg_][nbFlag] << std::endl; 
		if (cmd[flag_][nbFlag] == "+l")
			newMaxCli = cmd[flagArg_][nbFlag];
		executeFlag(cmd[flag_][nbFlag], cmd[flagArg_][nbFlag], curChan);
		newModes.append(cmd[flag_][nbFlag]);
	}
	newModes.append(" ");
	newModes.append(newMaxCli);
	sendMessageChannel(curChan.getCliInChan(),
					   RPL_CHANNELMODEIS(sender->cliInfo.getNick(),
										 curChan.getName(), newModes));
	curChan.setModes();
}
