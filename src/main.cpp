/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:11:56 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/13 16:45:07 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include "CmdManager.hpp"
#include <iostream>
#include <csignal>
#include <cstdlib>

int gSign = false;
int gPort = 0;
std::string gPassword = "";

void SignalHandler(int signum)
{
	(void)signum;
	gSign = true;
}


int main(int argc, char **argv) {
	Client client;
	std::vector< std::string > buffer;
	CmdManager cmManager;

	if (argc < 2)
		return (1);
	for (int i = 2; i < argc; i++) {
		buffer.push_back(argv[i]);
	}
	client.cliInfo.setRegistration(3);

	//create the map with all registered commands
	cmManager.generateCmds();

	//execute command
	try {
		cmManager.executeCm(cmManager.getCmd(argv[1]).process(buffer, client));
	} catch (const CmdManager::CmdNotFoundException &e) {
		std::cout << ERR_UNKNOWNCOMMAND(client.cliInfo.getNick(), argv[1]);
	}
}