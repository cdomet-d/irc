/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_join.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:49:17 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/24 19:21:44 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Exceptions.hpp"
#include "validator.hpp"

bool check::join(CmdSpec &cmd, size_t idx) {
	while (idx < cmd[channel_].size()) {
		try {
			Channel &curChan = cmd.serv_.findChan(cmd[channel_][idx]);
			if (!check::join_::assessRequest(curChan, cmd, idx)) {
				cmd[channel_].rmParam(idx);
				continue;
			}
		} catch (ObjectNotFound &e) {
			if (!check::join_::chanSyntaxIsValid(cmd, idx)) {
				cmd[channel_].rmParam(idx);
				continue;
			} else
				check::len(cmd, idx);
		}
		if (check::join_::cliHasMaxChans(cmd, idx)) {
			cmd[channel_].rmParam(idx);
			continue;
		}
		idx++;
	}
	if (!cmd[channel_].size())
		return false;
	return true;
}

bool check::join_::assessRequest(const Channel &chan, CmdSpec &cmd,
								 size_t idx) {
	if (check::chans_::onChan(cmd[channel_][idx],
							  cmd.getSender().getJoinedChans()))
		return (false);
	if (chan.getModes().find('l') != std::string::npos &&
		!check::join_::chanHasRoom(chan, cmd.getSender()))
		return (false);
	if (chan.getModes().find("i") != std::string::npos) {
		if (!check::join_::hasInvite(chan, cmd.getSender()))
			return (false);
	} else if (chan.getModes().find("k") != std::string::npos &&
			   !check::join_::validKey(chan, cmd[key_], idx, cmd.getSender()))
		return (false);
	return (true);
}

bool check::join_::hasInvite(const Channel &chan, Client &sender) {
	clientMap::const_iterator itCli;

	itCli = chan.getInvitCli().find(sender.getFd());
	if (itCli != chan.getInvitCli().end())
		return (true);
	RPL::send_(sender.getFd(),
			   ERR_INVITEONLYCHAN(sender.cliInfo.getNick(), chan.getName()));
	return (false);
}

bool check::join_::validKey(const Channel &chan, CmdParam &keys, size_t idx,
							Client &sender) {
	if (idx < keys.size() && chan.getPassword() == keys[idx])
		return (true);
	RPL::send_(sender.getFd(),
			   ERR_BADCHANNELKEY(sender.cliInfo.getNick(), chan.getName()));
	return (false);
}

bool check::join_::chanHasRoom(const Channel &chan, Client &sender) {
	if (chan.getCliInChan().size() < static_cast< size_t >(chan.getMaxCli()))
		return (true);
	RPL::send_(sender.getFd(),
			   ERR_CHANNELISFULL(sender.cliInfo.getNick(), chan.getName()));
	return (false);
}

bool check::join_::cliHasMaxChans(const CmdSpec &cmd, size_t idx) {
	if (cmd[channel_][idx] == "0" ||
		cmd.getSender().getJoinedChans().size() + idx < MAX_CHAN_PER_CLI)
		return (false);
	RPL::send_(cmd.getSdFd(),
			   ERR_TOOMANYCHANNELS(cmd.getSdNick(), cmd[channel_][idx]));
	return (true);
}

bool check::join_::chanSyntaxIsValid(const CmdSpec &cmd, size_t idx) {
	if (cmd[channel_][idx] == "0")
		return (true);
	if (cmd[channel_][idx][0] != '#' ||
		cmd[channel_][idx].find(" ") != std::string::npos) {
		RPL::send_(cmd.getSender().getFd(),
				   ERR_NOSUCHCHANNEL(cmd.getSender().cliInfo.getNick(),
									 cmd[channel_][idx]));
		return false;
	}
	return true;
}
