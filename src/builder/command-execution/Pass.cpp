/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 09:04:38 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/20 10:41:22 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "typedef.hpp"
#include <sstream>

bool passExec(std::string params, Client *curCli)
{
	logLevel(DEBUG, "----passExec----");
	static Server &server = Server::GetServerInstance(0, "");

	std::istringstream iss(params);
	std::string password, command = "PASS", placeHolder = "*";


	getline(iss, password);

	if (password.empty() == true) {
		sendReply(curCli->getFd(), ERR_NEEDMOREPARAMS(command));
		return (false);
	}

	clientMapIt senderIt = server.getAllCli().find(curCli->getFd());
	if (server.getAllCli().size() == 0 &&
		senderIt != server.getAllCli().end()) {
		sendReply(curCli->getFd(), ERR_ALREADYREGISTRED());
		return (false);
	}

	if (password != server.getPass()) {
		sendReply(curCli->getFd(), ERR_PASSWDMISMATCH(placeHolder));
		return (false);
	}

	sendReply(curCli->getFd(), PASS_SUCCESS());

	return (true);
}