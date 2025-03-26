/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_chan.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:49:17 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/26 14:22:29 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.hpp"

bool check::chan(CmdSpec &cmd) {
	stringVec param = cmd[channel_].getInnerParam();
	return (true);
}

bool check::join_::valid::request(Channel chan, CmdSpec &cmd, size_t i) {
	if (onChan(cmd))
		return (false);
	if (reachedChanLimit(chan, cmd.getSender()))
		return (false);
	if (chan.getModes().find("i") != std::string::npos &&
		!hasInvite(chan, cmd.getSender()))
		return (false);
	else if (chan.getModes().find("k") != std::string::npos &&
			 !validKey(chan, cmd[key_], i, cmd.getSender()))
		return (false);
	if (reachedCliChanLimit(chan, cmd.getSender()))
		return (false);
	return (true);
}

bool assessRequest(CmdSpec &cmd) {
	channelMap::const_iterator itChan;

	for (size_t i = 0; i < cmd[channel_].size(); i++) {
		//TODO: call coralie's function to check syntax of channel
		itChan = cmd.server_.getAllChan().find(cmd[channel_][i]);
		if (itChan == cmd.server_.getAllChan().end())
			continue;
		if (!check::join_::valid::request(*itChan->second, cmd, i))
			cmd[channel_].rmParam(i);
	}
	if (!cmd[channel_].size())
		return (false);
	return (true);
}

bool onChan(CmdSpec &cmd) {
	const stringVec &joinedChans = cmd.getSender().getJoinedChans();
	for (size_t i = 0; i < joinedChans.size(); i++) {
		if (joinedChans[i] == cmd[channel_][0])
			return (true);
	}
	if (cmd.getName() != "JOIN")
		reply::send(cmd.getSender().getFd(),
					ERR_NOTONCHANNEL(cmd.getSender().cliInfo.getNick(),
									 cmd[channel_][0]));
	return (false);
}

bool hasChanPriv(CmdSpec &cmd) {
	channelMap::const_iterator itChan;

	itChan = cmd.server_.getAllChan().find(cmd[channel_][0]);
	Channel chan = *itChan->second;

	if (cmd.getName() == "TOPIC" &&
		(!cmd[topic_].getInnerParam().empty() ||
		 (chan.getModes().find('t') == std::string::npos))) {
		return (true);
	}

	clientMap::const_iterator itCl;

	itCl = chan.getOpCli().find(cmd.getSender().getFd());
	if (itCl == chan.getOpCli().end()) {
		reply::send(cmd.getSender().getFd(),
					ERR_CHANOPRIVSNEEDED(cmd.getSender().cliInfo.getNick(),
										 chan.getName()));
		return (false);
	}
	return (true);
}

bool reachedChanLimit(Channel &chan, Client &sender) {
	if (chan.getModes().find('l') == std::string::npos ||
		chan.getCliInChan().size() < chan.getMaxCli())
		return (false);
	reply::send(sender.getFd(), ERR_CHANNELISFULL(chan.getName()));
	return (true);
}

bool hasInvite(Channel &chan, Client &sender) {
	clientMap::const_iterator itCli;

	itCli = chan.getInvitCli().find(sender.getFd());
	if (itCli != chan.getInvitCli().end())
		return (true);
	reply::send(sender.getFd(), ERR_INVITEONLYCHAN(chan.getName()));
	return (false);
}

// TODO: couldn't we use pwMatch here ? 	
bool validKey(Channel &chan, CmdParam &keys, size_t i,
						 Client &sender) {
	if (i < keys.size() && chan.getPassword() == keys[i])
		return (true);
	reply::send(sender.getFd(),
				ERR_BADCHANNELKEY(sender.cliInfo.getNick(), chan.getName()));
	return (false);
}

bool reachedCliChanLimit(Channel &chan, Client &sender) {
	//TODO: faire un define pour client chan limit
	if (sender.getJoinedChans().size() < 50)
		return (false);
	reply::send(sender.getFd(), ERR_TOOMANYCHANNELS(chan.getName()));
	return (true);
}
