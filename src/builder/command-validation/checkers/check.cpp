/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:15:18 by csweetin          #+#    #+#             */
/*   Updated: 2025/04/11 15:11:42 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printers.hpp"
#include "validator.hpp"

bool check::len(CmdSpec &cmd, size_t idx) {
	std::string cmdName[5] = {"JOIN", "NICK", "USER", "TOPIC", "KICK"};
	size_t i = 0;
	while (i < 5 && cmdName[i] != cmd.getName())
		i++;
	switch (i) {
	case 0:
		return (cmd[channel_].trimParam(idx, CHANNELLEN));
	case 1:
		return (cmd[nickname_].trimParam(idx, NICKLEN));
	case 2:
		return (cmd[username_].trimParam(idx, USERLEN));
	case 3:
		if (!cmd[topic_].empty())
			return (cmd[topic_].trimParam(idx, TOPICLEN));
		break;
	case 4:
		if (!cmd[message_].empty())
			return (cmd[message_].trimParam(idx, KICKLEN));
		break;
	default:
		return true;
	}
	return true;
}

bool check::user(CmdSpec &cmd, size_t idx) {
	if (!check::nick_::syntaxIsValid(cmd[username_][idx], cmd.getSender()))
		return false;
	if (cmd[hostname_][idx] != "0" || cmd[servername_][idx] != "*") {
		std::string reply = cmd[username_][idx] + " " + cmd[hostname_][idx] +
							" " + cmd[servername_][idx] + " " +
							cmd[realname_][idx];
		RPL::send_(cmd.getSdFd(),
				   ERR_BADINPUT(cmd.getName(), USERFORMAT, reply));
		return false;
	}
	return true;
}

/* check that the target exists */
bool check::target(CmdSpec &cmd, size_t idx) {
	if (!check::exists(cmd[target_][idx], cmd.serv_.getUsedNick())) {
		RPL::send_(cmd.getSdFd(),
				   ERR_NOSUCHNICK(cmd.getSdNick(), cmd[target_][idx]));
		return false;
	}
	return true;
}

/* check that the target is not already on the chan */
bool check::invite(CmdSpec &cmd, size_t idx) {
	if (!check::target(cmd, idx))
		return false;
	const stringVec &tChan = check::getTargetChan(cmd[target_][idx], cmd.serv_);
	if (check::chans_::onChan(cmd[channel_][idx], tChan)) {
		RPL::send_(cmd.getSdFd(),
				   ERR_USERONCHANNEL(cmd.getSdNick(), cmd[target_][idx],
									 cmd[channel_][idx]));
		return false;
	}
	return true;
}

bool check::enoughParams(CmdSpec &cmd, size_t idx) {
	while (idx < cmd.getParams().size()) {
		CmdParam &innerParam = *cmd.getParams()[idx].second;
		if (!innerParam.isOpt() &&
			(innerParam.empty() || innerParam[0].empty())) {
			RPL::send_(cmd.getSdFd(),
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