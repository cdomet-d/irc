/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_chans.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:03:05 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/31 18:41:16 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.hpp"

bool check::chans_::isOnChan(CmdSpec &cmd, int idx) {
	stringVec joinedChans = cmd.getSender().getJoinedChans();

	if (!check::findString(joinedChans, cmd[channel_][idx])) {
		reply::send_(cmd.getSender().getFd(),
					 ERR_NOTONCHANNEL(cmd.getSender().cliInfo.getNick(),
									  cmd[channel_][idx]));
		return (false);
	}
	return (true);
}

bool check::chans_::hasChanAuthorisations(CmdSpec &cmd, int idx) {
	(void)idx;
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
