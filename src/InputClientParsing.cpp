/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InputClientParsing.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:23:33 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/04 18:42:07 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>

std::vector< std::string > VectorSplit(std::string &s,
									   const std::string &delimiter)
{
	std::vector< std::string > inputCli;
	size_t pos = 0;
	std::string token;

	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		inputCli.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	inputCli.push_back(s);

	return (inputCli);
}

void inputToken(std::string inputCli, int fd) {
	std::istringstream iss(inputCli);

	std::string command;
	std::string params;

	//starts with clean strings
	command.clear();
	params.clear();

	iss >> command;
	std::getline(iss, params);
	
	log(DEBUG, "Command = ", command);
	log(DEBUG, "params = ", params);
	
	if (command == "JOIN") {
		handleJoin(params, fd);
		return ; }
	if (command == "PRIVMSG") {
		handlePrivsmg(params, fd);
		return ; }

	//clean the istringstream
	iss.str("");
	iss.clear();
}