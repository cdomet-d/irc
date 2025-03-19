/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinRequestCheck.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:53:59 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/19 18:36:42 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JoinRequestCheck.hpp"
#include "Checkers.hpp"

bool joinCheck::reachedChanLimit(Channel &chan, Client &sender) {
	if (chan.getCliInChan().size() < chan.getMaxCli())
		return (false);
	reply::send(sender.getFd(), ERR_CHANNELISFULL(chan.getName()));
	return (true);
}

bool joinCheck::hasInvite(Channel &chan, Client &sender) {

	if (/*&& sender doesn't have an invite*/) {
		reply::send(sender.getFd(), ERR_INVITEONLYCHAN(chan.getName()));
		return (false);
	}
	return (true);
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
