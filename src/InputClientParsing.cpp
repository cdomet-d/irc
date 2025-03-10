/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InputClientParsing.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:23:33 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/10 09:13:42 by aljulien         ###   ########.fr       */
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

void inputToken(std::string inputCli, Client *currentCli)
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
		handleJoin(params, currentCli);
		return;
	}
	if (command == "PRIVMSG") {
		handlePrivsmg(params, currentCli);
		return;
	}
	if (command == "TOPIC") {
		handleTopic(params, currentCli);
		return ;
	}
	if (command == "MODE") {
		//handleMode(currentCli)
		std::cout << "its mode guys" << std::endl;
		return ;
	}
	if (command == "PART") {
		handlePart(params, currentCli);
		return ;
	}

	//clean the istringstream
	iss.str("");
	iss.clear();
}