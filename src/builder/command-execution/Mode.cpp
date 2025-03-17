/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:43:39 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/17 13:21:36 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>

/* void removeModes(Client * curCli, Channel *curChan, std::string modes) {
	for (size_t i = 0; modes.c_str()[i] != '+'; i++) {
		if (modes.c_str()[i] == 'i')
			curChan->setInviteOnly(true);
	//	if (modes.c_str()[i] == 'i')
	}
}

void addModes(Client * curCli, Channel *curChan, std::string modes) {
	
}

bool handleChannelMode(Client * curCli, std::string chanName, std::string modes) {
	static Server &server = Server::GetServerInstance(0, "");
	
	//does the channel exist ?
	channelMapIt curChanIt = server.getAllChan().find(chanName);
	if (curChanIt == server.getAllChan().end()) {
		sendReply(curCli->getFd(),
				  ERR_NOSUCHCHANNEL(curCli->getNick(), chanName));
		log(DEBUG, "PART", "ERR_NOSUCHCHANNEL");
		return (false);
	}
	Channel *curChan = curChanIt->second;

	//returns the current mode of a channel : RPL_CHANNELMODEIS (324)
	if (modes == " ") {
		sendReply(curCli->getFd(), RPL_CHANNELMODEIS(curCli->getNick(), chanName));
		log(DEBUG, "Checking the mode: ",
			RPL_CHANNELMODEIS(curCli->getNick(), chanName));
		return (true);
	}

	//isCliOp ?
	clientMapIt senderIt =
		curChanIt->second->getOpCli().find(curCli->getFd());
	if (senderIt == curChanIt->second->getCliInChan().end()) {
		sendReply(curCli->getFd(),
				  ERR_CHANOPRIVSNEEDED(curCli->getNick(), chanName));
		log(DEBUG, "PART", "ERR_CHANOPRIVSNEEDED");
		return (false);
	}
	log(DEBUG, "Client is operator");

	for(size_t i = 0; i <  modes.size(); i++) {
		if (modes.c_str()[i] == '-') {
			modes.erase(i, 1);
			removeModes(curCli, curChan, modes);
		}
		if (modes.c_str()[i] == '+') {
			modes.erase(i, 1);
			addModes(curCli, curChan, modes);
		}
	}
	
	return (false);
	//change the modes
}

bool handleUserMode(Client *curCli, std::string userName, std::string modes) {
	(void)curCli;
	(void)userName;
	(void)modes;
	return (false);
}
*/

// Helper function to check if a flag requires parameters
static bool requiresParameter(const std::string& flag) {
    return flag != "+i" && flag != "+t";
}

void parseInput(const std::string& input, 
                std::vector<std::string>& flags, 
                std::vector<std::string>& params) {
    // Clear output vectors
    flags.clear();
    params.clear();
    
    // Split input into tokens
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    
    // Separate flags and parameters
    std::vector<std::string> parameters_tokens;
    bool in_flags_section = true;
    
    for (std::vector<std::string>::const_iterator it = tokens.begin(); 
         it != tokens.end(); ++it) {
        if (in_flags_section && !it->empty() && (*it)[0] == '+') {
            flags.push_back(*it);
        } else {
            in_flags_section = false;
            parameters_tokens.push_back(*it);
        }
    }
    
    // Initialize parameters with empty strings
    params.resize(flags.size());
    
    // Assign parameters to flags that require them
    size_t param_index = 0;
    for (size_t i = 0; i < flags.size(); ++i) {
        if (requiresParameter(flags[i])) {
            if (param_index < parameters_tokens.size()) {
                params[i] = parameters_tokens[param_index];
                ++param_index;
            }
        }
    }
}

void printVector(const std::vector<std::string>& vec) {
    for (std::vector<std::string>::const_iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << std::endl;
    }
}

void executeO(std::string flag, std::string param) {
	if (flag.find("+") != std::string::npos) {
		
	} else {
		
	}
}

void executeI(std::string flag, std::string param) {
	
}
void executeT (std::string flag, std::string param) {

}

void executeK(std::string flag, std::string param) {
	
}

void executeL(std::string flag, std::string param) {
	
}

int findFlagLevel(std::string level) {
	std::string flag[5] = {"o", "i", "t", "k", "l"};
	for (int i = 0; i < 5; i++) { 
		if (level.find(flag[i]) != std::string::npos)
			return (i);
	}
	return (-1);
}

void executeFlag(std::string flag, std::string param) {
	p_to_f flagExecutor[5] = {&executeO, &executeI, &executeT, &executeK, &executeL};
	int flagLevel = findFlagLevel(flag);

	if (flagLevel != -1)
		flagExecutor[flagLevel](flag, param);
	else
		log(DEBUG, "Invalid flag");
}

//the modes of a channel need to be empty if no moe is activated and +<modes> if any
bool handleMode(std::string params, Client *curCli)
{
	log(DEBUG, "HandleMode");
	(void)curCli;

	std::vector<std::string> flags, param;
	
	parseInput(params, flags, param);

	std::cout << "FLAGS :" << std::endl;
	printVector(flags);
	std::cout << std::endl << "PARAMS :" << std::endl;
	printVector(param);
	
	for (size_t nbFlag = 0; nbFlag < flags.size(); nbFlag++)
		executeFlag(flags[nbFlag], param[nbFlag]);
	return (true);
}


//