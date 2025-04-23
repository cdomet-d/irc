/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:55:57 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/23 17:25:10 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Server.hpp"

static void checkTopic(const Channel &curChan, const Client &curCli) {
	if (curChan.getTopic().empty() == true) {
		RPL::send_(curCli.getFd(),
				   RPL_NOTOPIC(curCli.cliInfo.getNick(), curChan.getName()));
		return;
	}
	RPL::send_(curCli.getFd(),
			   RPL_TOPIC(curCli.cliInfo.getNick(), curChan.getName(),
						 curChan.getTopic()));
	return;
}

static void changeTopic(Channel &curChan, const Client &curCli, const std::string &topic) {
	curChan.setTopic(topic);
	RPL::sendMessageChannel(curChan.getCliInChan(),
							RPL_TOPICCHANGED(curCli.cliInfo.getPrefix(),
											 curChan.getName(),
											 curChan.getTopic()));
}

void topic(CmdSpec &cmd) {
	Client &sender = cmd.getSender();

	try {
		Channel &curChan = cmd.serv_.findChan(cmd[channel_][0]);

		if (!cmd[topic_].size())
			checkTopic(curChan, sender);
		else
			changeTopic(curChan, sender, cmd[topic_][0]);
	} catch (std::exception &e) { RPL::log(RPL::ERROR, e.what()); }
}
