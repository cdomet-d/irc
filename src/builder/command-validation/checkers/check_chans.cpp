/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_chans.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:03:05 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/01 08:34:19 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.hpp"

bool check::chans_::isOnChan(CmdSpec &cmd) {
	stringVec joinedChans = cmd.getSender().getJoinedChans();
	size_t i = 0;

	while (i < cmd[channel_].size()) {
		if (!findString(joinedChans, cmd[channel_][i])) {
			reply::send_(cmd.getSender().getFd(),
						 ERR_NOTONCHANNEL(cmd.getSender().cliInfo.getNick(),
										  cmd[channel_][i]));
			cmd[channel_].rmParam(i);
			continue;
		}
		i++;
	}
	if (!cmd[channel_].size())
		return (false);
	return (true);
}

bool check::chans_::hasChanAuthorisations(CmdSpec &cmd) {
	channelMap::const_iterator itChan;

	itChan = cmd.server_.getAllChan().find(cmd[channel_][0]);
	Channel chan = *itChan->second;

	if (cmd.getName() == "TOPIC" &&
		(cmd[topic_].empty() ||
		 chan.getModes().find('t') == std::string::npos)) {
		return (true);
	}

	clientMap::const_iterator itCl;

	itCl = chan.getOpCli().find(cmd.getSender().getFd());
	if (itCl == chan.getOpCli().end()) {
		reply::send_(cmd.getSender().getFd(),
					 ERR_CHANOPRIVSNEEDED(cmd.getSender().cliInfo.getNick(),
										  chan.getName()));
		return (false);
	}
	return (true);
}
