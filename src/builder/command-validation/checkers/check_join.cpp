/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_join.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:49:17 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/15 10:46:31 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.hpp"

bool check::join(CmdSpec &cmd, size_t idx) {
	Channel *currChan;

	while (idx < cmd[channel_].size()) {
		currChan = cmd.serv_.findChan(cmd[channel_][idx]);
		if (currChan != NULL) {
			if (!check::join_::assessRequest(*currChan, cmd, idx)) {
				cmd[channel_].rmParam(idx);
				continue;
			}
		} else if (!check::join_::syntaxIsValid(cmd, idx)) {
			cmd[channel_].rmParam(idx);
			continue;
		}
		else
			check::len(cmd, idx);
		idx++;
	}
	if (!cmd[channel_].size())
		return (false);
	return (true);
}

bool check::join_::assessRequest(Channel chan, CmdSpec &cmd, size_t idx) {
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
	if (check::join_::cliHasMaxChans(chan, cmd.getSender()))
		return (false);
	return (true);
}

bool check::join_::hasInvite(Channel &chan, Client &sender) {
	clientMap::const_iterator itCli;

	itCli = chan.getInvitCli().find(sender.getFd());
	if (itCli != chan.getInvitCli().end())
		return (true);
	RPL::send_(sender.getFd(),
			   ERR_INVITEONLYCHAN(sender.cliInfo.getNick(), chan.getName()));
	return (false);
}

bool check::join_::validKey(Channel &chan, CmdParam &keys, size_t idx,
							Client &sender) {
	if (idx < keys.size() && chan.getPassword() == keys[idx])
		return (true);
	RPL::send_(sender.getFd(),
			   ERR_BADCHANNELKEY(sender.cliInfo.getNick(), chan.getName()));
	return (false);
}

bool check::join_::chanHasRoom(Channel &chan, Client &sender) {
	if (chan.getCliInChan().size() < chan.getMaxCli())
		return (true);
	RPL::send_(sender.getFd(),
			   ERR_CHANNELISFULL(sender.cliInfo.getNick(), chan.getName()));
	return (false);
}

bool check::join_::cliHasMaxChans(Channel &chan, Client &sender) {
	if (sender.getJoinedChans().size() < MAX_CHAN_PER_CLI)
		return (false);
	RPL::send_(sender.getFd(),
			   ERR_TOOMANYCHANNELS(sender.cliInfo.getNick(), chan.getName()));
	return (true);
}

bool check::join_::syntaxIsValid(CmdSpec &cmd, size_t idx) {
	if (cmd[channel_][idx].size() == 1 && cmd[channel_][idx][0] == '0')
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
