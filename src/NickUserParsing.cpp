/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickUserParsing.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:22:45 by aljulien          #+#    #+#             */
/*   Updated: 2025/02/25 15:23:23 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::string handleNick(std::string &buffer) {
	log(DEBUG, "-----handleNick-----");
	
	if (buffer.find("NICK") != buffer.npos)
		buffer.erase(buffer.find("NICK"), 5);
	return (buffer);
}

std::string handleUsername(std::string &buffer) {
	log(DEBUG, "-----handleUser-----");
	
	std::string user;
	if (buffer.find("USER") != buffer.npos)
		buffer.erase(buffer.find("USER"), 5);
	std::string::iterator it = buffer.begin();
	for (; *it != ' '; ++it)
		user.push_back(*it);
	return (user);
}