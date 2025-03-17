/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:43:39 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/17 14:03:30 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>

static bool requiresParameter(const std::string &flag)
{
	return flag != "+i" && flag != "+t";
}

void parseInput(const std::string &input, std::vector< std::string > &flags,
				std::vector< std::string > &params)
{
	flags.clear();
	params.clear();

	std::istringstream iss(input);
	std::vector< std::string > tokens;
	std::string token;
	while (iss >> token) {
		tokens.push_back(token);
	}

	std::vector< std::string > parameters_tokens;
	bool in_flags_section = true;

	for (std::vector< std::string >::const_iterator it = tokens.begin();
		 it != tokens.end(); ++it) {
		if (in_flags_section && !it->empty() && (*it)[0] == '+') {
			flags.push_back(*it);
		} else {
			in_flags_section = false;
			parameters_tokens.push_back(*it);
		}
	}
	params.resize(flags.size());

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

void printVector(const std::vector< std::string > &vec)
{
	for (std::vector< std::string >::const_iterator it = vec.begin();
		 it != vec.end(); ++it) {
		std::cout << *it << std::endl;
	}
}

void executeO(std::string flag, std::string param)
{
	(void)flag;
	(void)param;
	//if (flag.find("+") != std::string::npos) {
	//
	//} else {
	//
	//}
}

void executeI(std::string flag, std::string param)
{
	(void)flag;
	(void)param;
}
void executeT(std::string flag, std::string param)
{
	(void)flag;
	(void)param;
}

void executeK(std::string flag, std::string param)
{
	(void)flag;
	(void)param;
}

void executeL(std::string flag, std::string param)
{
	(void)flag;
	(void)param;
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

void executeFlag(std::string flag, std::string param)
{
	p_to_f flagExecutor[5] = {&executeO, &executeI, &executeT, &executeK,
							  &executeL};
	int flagLevel = findFlagLevel(flag);

	if (flagLevel != -1)
		flagExecutor[flagLevel](flag, param);
	else
		log(DEBUG, "Invalid flag");
}

//the modes of a channel need to be empty if no moe is activated and +<modes> if any
//TODO the first params will be the nam of the channel
bool handleMode(std::string params, Client *curCli)
{
	log(DEBUG, "HandleMode");
	(void)curCli;

	std::vector< std::string > flags, param;

	parseInput(params, flags, param);

	std::cout << "FLAGS :" << std::endl;
	printVector(flags);
	std::cout << std::endl << "PARAMS :" << std::endl;
	printVector(param);

	for (size_t nbFlag = 0; nbFlag < flags.size(); nbFlag++)
		executeFlag(flags[nbFlag], param[nbFlag]);
	return (true);
}
