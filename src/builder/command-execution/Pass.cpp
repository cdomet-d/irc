/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlotte <charlotte@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 09:04:38 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/20 12:58:55 by charlotte        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "typedef.hpp"
#include <sstream>

bool handlePass(std::string params, Client *curCli)
{
	reply::log(reply::DEBUG, "----handlePass----");
	static Server &server = Server::GetServerInstance(0, "");

	std::istringstream iss(params);
	std::string password, command = "PASS", placeHolder = "*";


	getline(iss, password);

	if (password.empty() == true) {
		reply::send(curCli->getFd(), ERR_NEEDMOREPARAMS(curCli->cliInfo.getNick(), command));
		return (false);
	}

	clientMapIt senderIt = server.getAllCli().find(curCli->getFd());
	if (server.getAllCli().size() == 0 &&
		senderIt != server.getAllCli().end()) {
		reply::send(curCli->getFd(), ERR_ALREADYREGISTRED(curCli->cliInfo.getNick()));
		return (false);
	}

	if (password != server.getPass()) {
		reply::send(curCli->getFd(), ERR_PASSWDMISMATCH(placeHolder));
		return (false);
	}

	reply::send(curCli->getFd(), PASS_SUCCESS());

	return (true);
}

#include "CmdSpec.hpp"
void pass(CmdSpec &cmd) {
	cmd.getSender().cliInfo.setRegistration(1);
}