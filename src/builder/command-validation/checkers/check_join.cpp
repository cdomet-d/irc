/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_join.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:49:17 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/09 13:40:37 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.hpp"

bool check::join(CmdSpec &cmd, size_t idx) {
	channelMap::const_iterator itChan;

	while (idx < cmd[channel_].size()) {
		itChan = cmd.serv_.getAllChan().find(cmd[channel_][idx]);
		if (itChan != cmd.serv_.getAllChan().end()) {
			if (!check::join_::assessRequest(*itChan->second, cmd, idx)) {
				cmd[channel_].rmParam(idx);
				continue;
			}
		} else if (!check::join_::syntaxIsValid(cmd, idx)) {
			cmd[channel_].rmParam(idx);
			continue;
		}
		idx++;
	}
	if (!cmd[channel_].size())
		return (false);
	return (true);
}

bool check::join_::assessRequest(Channel chan, CmdSpec &cmd, size_t idx) {
	if (check::chans_::onChan(cmd[channel_][idx], cmd.getSender().getJoinedChans()))
		return (false);
	if (!check::join_::chanHasRoom(chan, cmd.getSender()))
		return (false);
	if (chan.getModes().find("i") != std::string::npos &&
		!check::join_::hasInvite(chan, cmd.getSender()))
		return (false);
	else if (chan.getModes().find("k") != std::string::npos &&
			 !check::join_::validKey(chan, cmd[key_], idx, cmd.getSender()))
		return (false);
	if (check::join_::cliHasMaxChans(chan, cmd.getSender()))
		return (false);
	return (true);
}

bool check::join_::hasInvite(Channel &chan, Client &sender) {
	clientMap::const_iterator itCli;

	itCli = chan.getInvitCli().find(sender.getFd());
	if (itCli != chan.getInvitCli().end())
		return (true);
	reply::send_(sender.getFd(),
				 ERR_INVITEONLYCHAN(sender.cliInfo.getNick(), chan.getName()));
	return (false);
}

bool check::join_::validKey(Channel &chan, CmdParam &keys, size_t idx,
							Client &sender) {
	if (idx < keys.size() && chan.getPassword() == keys[idx])
		return (true);
	reply::send_(sender.getFd(),
				 ERR_BADCHANNELKEY(sender.cliInfo.getNick(), chan.getName()));
	return (false);
}

bool check::join_::chanHasRoom(Channel &chan, Client &sender) {
	if (chan.getModes().find('l') == std::string::npos ||
		chan.getCliInChan().size() < chan.getMaxCli())
		return (true);
	reply::send_(sender.getFd(),
				 ERR_CHANNELISFULL(sender.cliInfo.getNick(), chan.getName()));
	return (false);
}

bool check::join_::cliHasMaxChans(Channel &chan, Client &sender) {
	if (sender.getJoinedChans().size() < MAX_CHAN_PER_CLI)
		return (false);
	reply::send_(sender.getFd(),
				 ERR_TOOMANYCHANNELS(sender.cliInfo.getNick(), chan.getName()));
	return (true);
}

bool check::join_::syntaxIsValid(CmdSpec &cmd, size_t idx) {
	if (cmd[channel_][idx][0] != '#') {
		reply::send_(cmd.getSendFd(),
					 ERR_NOSUCHCHANNEL(cmd.getSendNick(),
									   cmd[channel_][idx]));
		return false;
	}
	return true;
}