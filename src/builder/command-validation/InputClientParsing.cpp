/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InputClientParsing.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:23:33 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/10 16:32:06 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MessageValidator.hpp"
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

std::vector< std::string > vectorSplit(std::string &s,
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
	return (inputCli);
}

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

void inputToken(std::string inputCli, Client *curCli)
{
	inputCli = removeNewlines(inputCli);
	MessageValidator::assess();
}