/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:55:57 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/15 11:54:09 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Server.hpp"

void checkTopic(Channel &curChan, Client *curCli) {
	if (curChan.getTopic().empty() == true) {
		RPL::send_(curCli->getFd(),
				   RPL_NOTOPIC(curCli->cliInfo.getNick(), curChan.getName()));
		return;
	}
	RPL::send_(curCli->getFd(),
			   RPL_TOPIC(curCli->cliInfo.getNick(), curChan.getName(),
						 curChan.getTopic()));
	return;
}

void changeTopic(Channel &curChan, Client *curCli, std::string topic) {
	curChan.setTopic(topic);
	sendMessageChannel(curChan.getCliInChan(),
					   RPL_TOPICCHANGED(curCli->cliInfo.getPrefix(),
										curChan.getName(), curChan.getTopic()));
}

void topic(CmdSpec &cmd) {
	Client *sender = &cmd.getSender();
	Channel &curChan = *cmd.serv_.findChan(cmd[channel_][0]);

	if (!cmd[topic_].size())
		checkTopic(curChan, sender);
	else
		changeTopic(curChan, sender, cmd[topic_][0]);
}
