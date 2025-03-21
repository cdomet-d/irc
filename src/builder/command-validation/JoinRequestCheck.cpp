/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinRequestCheck.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlotte <charlotte@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:53:59 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/21 12:44:33 by charlotte        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JoinRequestCheck.hpp"

bool joinCheck::reachedChanLimit(Channel &chan, Client &sender) {
	if (chan.getModes().find('l') == std::string::npos ||
		chan.getCliInChan().size() < chan.getMaxCli())
		return (false);
	reply::send(sender.getFd(), ERR_CHANNELISFULL(chan.getName()));
	return (true);
}

bool joinCheck::hasInvite(Channel &chan, Client &sender) {
	clientMap::const_iterator itCli;

	itCli = chan.getInvitCli().find(sender.getFd());
	if (itCli != chan.getInvitCli().end())
		return (true);
	reply::send(sender.getFd(), ERR_INVITEONLYCHAN(chan.getName()));
	return (false);
}

bool joinCheck::validKey(Channel &chan, CmdParam &keys, size_t i,
						 Client &sender) {
	if (i < keys.getSize() && chan.getPassword() == keys[i])
		return (true);
	reply::send(sender.getFd(),
				ERR_BADCHANNELKEY(sender.cliInfo.getNick(), chan.getName()));
	return (false);
}

bool joinCheck::reachedCliChanLimit(Channel &chan, Client &sender) {
	//TODO: faire un define pour client chan limit
	if (sender.getJoinedChans().size() < 50)
		return (false);
	reply::send(sender.getFd(), ERR_TOOMANYCHANNELS(chan.getName()));
	return (true);
}
