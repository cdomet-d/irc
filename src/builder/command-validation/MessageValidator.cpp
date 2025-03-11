/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageValidator.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:45:07 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/11 17:07:32 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MessageValidator.hpp"
#include "Reply.hpp"
#include <algorithm>
#include <iostream>

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */
bool MessageValidator::assess(const Client &sender) {

	std::string message = sender.getBuffer();
	if (lenIsValid(message, sender) == false)
		return false;
	if (hasPrefix(message, sender.getPrefix()) == false)
		return false;
	return true;
}

bool MessageValidator::hasPrefix(std::string &mess,
								 const std::string &cliPrefix) {
	if (mess.at(0) == ':') {
		std::string::size_type sep = mess.find(" ");
		if (sep != std::string::npos) {
			std::string prefix = mess.substr(1, (sep - 1));
			if (prefix != cliPrefix)
				return false;
			else
				mess.erase(0, (sep + 1));
		}
	}
	return true;
}

bool MessageValidator::hasTrailing(const std::string &mess) {
	std::string::const_iterator trail = find(mess.begin(), mess.end(), " :");
	
	if (trail != mess.end())
		
}

bool MessageValidator::lenIsValid(const std::string &mess,
								  const Client &sender) {
	if (mess.empty())
		return false;
	if (mess.size() > 512) {
		sendReply(sender.getFd(), sender.getNick());
		return false;
	}
	return true;
}

// std::string MessageValidator::getTrailing(const std::string &mess) {}
// stringVec MessageValidator::StructureIsValid(const std::string &mess) {}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */

/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */