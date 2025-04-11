/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:15:18 by csweetin          #+#    #+#             */
/*   Updated: 2025/04/09 15:19:06 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printers.hpp"
#include "validator.hpp"

// TODO: add syntax checks on username ?
/* checks that username syntax is valid */
bool check::user(CmdSpec &cmd, size_t idx) {
	cmd[username_].trimParam(idx, USERLEN);
	if (cmd[username_].size() < 1) {
		reply::send_(cmd.getSdFd(),
					 ERR_NEEDMOREPARAMS(cmd.getSdNick(), cmd.getName()));
		return false;
	}
	if (!check::nick_::syntaxIsValid(cmd[username_][idx], cmd.getSender()))
		return false;
	if (cmd[hostname_][idx] != "0" || cmd[servername_][idx] != "*") {
		std::string reply = cmd[username_][idx] + "] [" + cmd[hostname_][idx]
							+ "] [" + cmd[servername_][idx] + "] ["
							+ cmd[realname_][idx];
		reply::send_(cmd.getSdFd(), ERR_BADCHAR(cmd.getSdNick(), reply));
		return false;
	}
	return true;
}

/* check that the target exists */
bool check::target(CmdSpec &cmd, size_t idx) {
	if (!check::exists(cmd[target_][idx], cmd.serv_.getUsedNick())) {
		reply::send_(cmd.getSdFd(),
					 ERR_NOSUCHNICK(cmd.getSdNick(), cmd[target_][idx]));
		return false;
	}
	return true;
}

/* check that the target is not already on the chan */
bool check::invite(CmdSpec &cmd, size_t idx) {
	if (!check::target(cmd, idx))
		return false;
	const stringVec &tChan
		= check::getTargetChan(cmd[target_][idx], cmd.serv_);
	if (check::chans_::onChan(cmd[channel_][idx], tChan)) {
		reply::send_(cmd.getSdFd(),
					 ERR_USERONCHANNEL(cmd.getSdNick(), cmd[target_][idx],
									   cmd[channel_][idx]));
		return false;
	}
	return true;
}

bool check::enoughParams(CmdSpec &cmd, size_t idx) {
	while (idx < cmd.getParams().size()) {
		CmdParam &innerParam = *cmd.getParams()[idx].second;
		if (!innerParam.isOpt() && innerParam.empty()) {
			reply::send_(cmd.getSdFd(),
						 ERR_NEEDMOREPARAMS(cmd.getSdNick(), cmd.getName()));
			return (false);
		}
		idx++;
	}
	return (true);
}

const stringVec &check::getTargetChan(const std::string &target,
									  const Server &serv) {
	return serv.getAllCli()
		.find(serv.getFdFromNick(target))
		->second->getJoinedChans();
}