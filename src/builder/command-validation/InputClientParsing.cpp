/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InputClientParsing.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:23:33 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/11 10:37:33 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>

std::string removeNewlines(const std::string &input)
{
	std::string result;
	for (size_t i = 0; i < input.length(); ++i) {
		if (input[i] != '\r' && input[i] != '\n') {
			result += input[i];
		}
	}
	return result;
}

stringVec vectorSplit(std::string &s,
									   const std::string &del) {
	stringVec inputCli;
	size_t pos = 0;
	std::string token;

	while ((pos = s.find(del)) != std::string::npos) {
		token = s.substr(0, pos);
		inputCli.push_back(token);
		s.erase(0, pos + del.length());
	}
	if (!s.empty())
		inputCli.push_back(s);
	return (inputCli);
}

void inputToken(std::string inputCli, Client *curCli)
{
	inputCli = removeNewlines(inputCli);
	std::istringstream iss(inputCli);

	std::string command;
	std::string params;

	//starts with clean strings
	command.clear();
	params.clear();

	iss >> command;
	std::getline(iss, params);

	log(DEBUG, "Command =\t", command);
	log(DEBUG, "params =\t", params);

	if (command == "JOIN") {
		handleJoin(params, curCli);
		return;
	}
	if (command == "PRIVMSG") {
		handlePrivsmg(params, curCli);
		return;
	}
	if (command == "TOPIC") {
		handleTopic(params, curCli);
		return ;
	}
	if (command == "MODE") {
		handleMode(params, curCli);
		return ;
	}
	if (command == "PART") {
		handlePart(params, curCli);
		return ;
	}

	//clean the istringstream
	iss.str("");
	iss.clear();
}