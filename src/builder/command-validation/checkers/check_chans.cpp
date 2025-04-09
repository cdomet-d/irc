/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_chans.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:03:05 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/09 16:21:29 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printers.hpp"
#include "validator.hpp"
#include <algorithm>

bool check::chan(CmdSpec &cmd, size_t idx) {
	std::string channel;
	if (cmd.getName() == "PRIVMSG")
		channel = cmd[target_][idx];
	else
		channel = cmd[channel_][idx];

	if (!check::exists(channel, cmd.serv_.getAllChan())) {
		reply::send_(cmd.getSdFd(),
					 ERR_NOSUCHCHANNEL(cmd.getSdNick(), channel));
		return (false);
	}
	stringVec userChan = cmd.getSender().getJoinedChans();
	if (!check::chans_::onChan(channel, userChan)) {
		reply::send_(cmd.getSdFd(),
					 ERR_NOTONCHANNEL(cmd.getSdNick(), channel));
		return (false);
	}
	return (true);
}

bool check::chans_::onChan(std::string arg, const stringVec &arr) {
	return std::find(arr.begin(), arr.end(), arg) != arr.end();
}

bool check::chans_::isOp(CmdSpec &cmd, size_t idx) {
	channelMap::const_iterator itChan;
	itChan = cmd.serv_.getAllChan().find(cmd[channel_][idx]);
	Channel chan = *itChan->second;

	if ((cmd.getName() == "TOPIC" &&
			(cmd[topic_].empty() ||
			 chan.getModes().find('t') == std::string::npos)) ||
		(cmd.getName() == "MODE" && cmd[flag_].empty() &&
		 cmd[flagArg_].empty())) {
		return (true);
	}

	clientMap::const_iterator itCl;
	itCl = chan.getOpCli().find(cmd.getSender().getFd());
	if (itCl == chan.getOpCli().end()) {
		reply::send_(cmd.getSdFd(),
					 ERR_CHANOPRIVSNEEDED(cmd.getSdNick(), chan.getName()));
		return (false);
	}
	return (true);
}
