/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:43:39 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/21 18:31:55 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include <cerrno>
#include <cstdlib>
#include <limits>
#include <sstream>

void executeO(std::string flag, std::string targ, Channel &curChan) {
	Client *targetCli = NULL;
	//TODO: function looks for a client in a channel based on nick ?
	for (clientMapIt targetIt = curChan.getCliInChan().begin();
		 targetIt != curChan.getCliInChan().end(); ++targetIt) {
		if (targetIt->second->cliInfo.getNick() == targ) {
			targetCli = targetIt->second;
			break;
		}
	}

	if (targetCli == NULL)
		return;

	if (flag == "+o") {
		curChan.addCli(OPCLI, targetCli);
		RPL::send_(
			targetCli->getFd(),
			RPL_CHANOPE(targetCli->cliInfo.getNick(), curChan.getName()));
	}
	if (flag == "-o") {
		curChan.removeCli(OPCLI, targetCli->getFd());
		RPL::send_(
			targetCli->getFd(),
			RPL_CHANOPENOPE(targetCli->cliInfo.getNick(), curChan.getName()));
	}
}

void executeI(std::string flag, std::string param, Channel &curChan) {
	(void)param;

	if (flag == "+i" && curChan.getInviteOnly() == false) {
		curChan.setInviteOnly(true);
		curChan.setModes();
	}
	if (flag == "-i" && curChan.getInviteOnly() == true) {
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

		// if err of strtod, the maxCli of the channel will be set to the maxCi of
		// the server so 50
		if (errno == ERANGE || *endptr != '\0' || result < 0
			|| result > std::numeric_limits< int >::max()) {
			curChan.setMaxCli(50);
			curChan.setModes();
		} else {
			curChan.setMaxCli(static_cast< int >(result));
			curChan.setModes();
		}
	}
	if (flag == "-l" && static_cast< ssize_t >(curChan.getMaxCli()) != -1) {
		curChan.setMaxCli(-1);
		curChan.setModes();
	}
}

int findFlagLevel(std::string level) {
	std::string flag[5] = { "o", "i", "t", "k", "l" };
	for (int i = 0; i < 5; i++) {
		if (level.find(flag[i]) != std::string::npos)
			return (i);
	}
	return (-1);
}

void executeFlag(std::string flag, std::string param, Channel &curChan) {
	modesFunc flagExecutor[5]
		= { &executeO, &executeI, &executeT, &executeK, &executeL };
	int flagLevel = findFlagLevel(flag);

	if (flagLevel != -1)
		flagExecutor[flagLevel](flag, param, curChan);
	else
		RPL::log(RPL::DEBUG, "Invalid flag : ", flag);
}

void buildNewModeString(CmdSpec &cmd, Channel &curChan, Client *sender) {
	std::string negMode = "-";
	std::string posMode = "+";
	std::string newPassMaxCli;

	for (size_t nbFlag = 0; nbFlag < cmd[flag_].size(); ++nbFlag) {
		if (cmd[flag_][nbFlag] == "+l" || cmd[flag_][nbFlag] == "+k"
			|| cmd[flag_][nbFlag] == "+o" || cmd[flag_][nbFlag] == "-o")
			newPassMaxCli.append(cmd[flagArg_][nbFlag] + " ");
		if (cmd[flag_][nbFlag].find("+") != std::string::npos)
			posMode += cmd[flag_][nbFlag][1];
		if (cmd[flag_][nbFlag].find("-") != std::string::npos)
			negMode += cmd[flag_][nbFlag][1];
	}
	if (negMode.size() == 1) {
		RPL::sendMessageChannel(curChan.getCliInChan(),
								RPL_MODE(sender->cliInfo.getPrefix(),
										 curChan.getName(), posMode,
										 newPassMaxCli));
	} else if (posMode.size() == 1) {
		RPL::sendMessageChannel(curChan.getCliInChan(),
								RPL_MODE(sender->cliInfo.getPrefix(),
										 curChan.getName(), negMode,
										 newPassMaxCli));
	} else
		RPL::sendMessageChannel(curChan.getCliInChan(),
								RPL_MODE(sender->cliInfo.getPrefix(),
										 curChan.getName(), posMode + negMode,
										 newPassMaxCli));
}

void mode(CmdSpec &cmd) {
	Client *sender = &cmd.getSender();
	Channel &curChan = *cmd.serv_.findChan(cmd[channel_][0]);

	if (!cmd[flag_].size()) {
		std::string modeArgs;

		if (curChan.getModes().find("l") != std::string::npos) {
			std::stringstream sstream;
			std::string maxCli;
			sstream << curChan.getMaxCli();
			sstream >> maxCli;
			modeArgs += maxCli;
		}
		if (curChan.getModes().find("k") != std::string::npos) {
			modeArgs += (" " + curChan.getPassword());
		}
		RPL::send_(sender->getFd(),
				   RPL_CHANNELMODEIS(sender->cliInfo.getNick(),
									 curChan.getName(), curChan.getModes(),
									 modeArgs));
		return;
	}
	for (size_t nbFlag = 0; nbFlag < cmd[flag_].size(); ++nbFlag)
		executeFlag(cmd[flag_][nbFlag], cmd[flagArg_][nbFlag], curChan);
	buildNewModeString(cmd, curChan, sender);
	curChan.setModes();
}
