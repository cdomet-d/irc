/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_chans.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:03:05 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/04 12:48:05 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printers.hpp"
#include "validator.hpp"
#include <algorithm>

bool check::chan(CmdSpec &cmd, int idx) {
	if (!check::exists(cmd[channel_][idx], cmd.serv_.getAllChan())) {
		reply::send_(cmd.getSender().getFd(),
					 ERR_NOSUCHCHANNEL(cmd.getSender().cliInfo.getNick(),
									   cmd[channel_][idx]));
		return (false);
	}
	stringVec userChan = cmd.getSender().getJoinedChans();
	if (!check::chans_::onChan(cmd[channel_][idx], userChan)) {
		reply::send_(cmd.getSender().getFd(),
					 ERR_NOTONCHANNEL(cmd.getSender().cliInfo.getNick(),
									  cmd[channel_][idx]));
		return (false);
	}
	return (true);
}

bool check::chans_::onChan(std::string arg, const stringVec &arr) {
	return std::find(arr.begin(), arr.end(), arg) != arr.end();
}

bool check::chans_::hasChanAuthorisations(CmdSpec &cmd, int idx) {
	(void)idx;
	channelMap::const_iterator itChan;

	itChan = cmd.serv_.getAllChan().find(cmd[channel_][0]);
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
