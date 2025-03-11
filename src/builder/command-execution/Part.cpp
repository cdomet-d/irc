/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:12:52 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/11 11:24:10 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>

//use the define for the map of client and channel
bool handlePart(std::string params, Client *curCli) {

    static Server &server = Server::GetServerInstance(gPort, gPassword);

    std::istringstream iss(params);
    std::string chanName;
    std::string reason;

    iss >> chanName;
    std::getline(iss, reason);

    //needMoreParams
    if (chanName.empty() == true) {
        sendReply(curCli->getFd(), ERR_NEEDMOREPARAMS(curCli->getNick(), "PART"));
        log(DEBUG, "PART", "ERR_NEEDMOREPARAMS");
        return (false);
    }

    //noSuchChannel
    channelMapIt curChan = server.getAllChan().find(chanName);
    if (curChan == server.getAllChan().end()) {
        sendReply(curCli->getFd(), ERR_NOSUCHCHANNEL(curCli->getNick(), chanName));
        log(DEBUG, "PART", "ERR_NOSUCHCHANNEL");
        return (false);
    }
	//notOnChannel
    clientMap::iterator senderIt = curChan->second->getCliInChan().find(curCli->getFd());
    if (senderIt == curChan->second->getCliInChan().end()) {
        sendReply(curCli->getFd(), ERR_NOTONCHANNEL(curCli->getNick(), chanName));
        log(DEBUG, "PART", "ERR_NOTONCHANNEL");
        return (false);
    }

    //send part reply to clients of the channel
    for (clientMap::iterator itCli =
            curChan->second->getCliInChan().begin();
        itCli != curChan->second->getCliInChan().end(); ++itCli) {
        if (reason.empty() == true)
            sendReply(itCli->second->getFd(), RPL_PARTNOREASON(curCli->getPrefix(), chanName));
        else
            sendReply(itCli->second->getFd(), RPL_PARTREASON(curCli->getPrefix(), chanName, reason));
    }

    //is Client op on channel ?
    if (curChan->second->getOpCli().find(senderIt->second->getFd()) != curChan->second->getOpCli().end())
        curChan->second->getOpCli().erase(senderIt);
    curChan->second->getCliInChan().erase(senderIt);
    return (true);
}