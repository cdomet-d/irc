/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:15:18 by csweetin          #+#    #+#             */
/*   Updated: 2025/04/09 13:29:13 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printers.hpp"
#include "validator.hpp"

// TODO: add syntax checks on username ?
/* checks that username syntax is valid */
bool
check::user (CmdSpec &cmd, size_t idx) {
	cmd[username_].trimParam (idx, USERLEN);
	if (cmd[username_].size () < 1) {
		reply::send_ (cmd.getSendFd (),
					  ERR_NEEDMOREPARAMS (cmd.getSendNick (), "USER"));
		return false;
	}
	if (cmd[hostname_][idx][0] != '0' || cmd[servername_][idx][0] != '*') {
		std::string reply = cmd[username_][idx] + "] [" + cmd[hostname_][idx]
							+ "] [" + cmd[servername_][idx] + "] ["
							+ cmd[realname_][idx];
		reply::send_ (cmd.getSendFd (),
					  ERR_BADCHAR (cmd.getSendNick (), reply));
		return false;
	}
	return true;
}

/* check that the target exists */
bool
check::target (CmdSpec &cmd, size_t idx) {
	if (!check::exists (cmd[target_][idx], cmd.serv_.getUsedNick ())) {
		reply::send_ (cmd.getSendFd (),
					  ERR_NOSUCHNICK (cmd.getSendNick (), cmd[target_][idx]));
		return false;
	}
	return true;
}

/* check that the target is not already on the chan */
bool
check::invite (CmdSpec &cmd, size_t idx) {
	if (!check::target (cmd, idx))
		return false;
	const stringVec &tChan
		= check::getTargetChan (cmd[target_][idx], cmd.serv_);
	if (check::chans_::onChan (cmd[channel_][idx], tChan)) {
		reply::send_ (cmd.getSendFd (),
					  ERR_USERONCHANNEL (cmd.getSendNick (), cmd[target_][idx],
										 cmd[channel_][idx]));
		return false;
	}
	return true;
}

bool
check::enoughParams (CmdSpec &cmd, size_t idx) {
	while (idx < cmd.getParams ().size ()) {
		CmdParam &innerParam = *cmd.getParams ()[idx].second;
		if (!innerParam.isOpt () && innerParam.empty ()) {
			reply::send_ (
				cmd.getSendFd (),
				ERR_NEEDMOREPARAMS (cmd.getSendNick (), cmd.getName ()));
			return (false);
		}
		idx++;
	}
	return (true);
}

const stringVec &
check::getTargetChan (const std::string &target, const Server &serv) {
	return serv.getAllCli ()
		.find (serv.getFdFromNick (target))
		->second->getJoinedChans ();
}