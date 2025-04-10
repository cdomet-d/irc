/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:58:28 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/10 17:12:48 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printers.hpp"
#include "validator.hpp"

/* Returns SET, UNSET or SET_ERR */
e_mdeset check::mode_::whichSet(const char &c) {
	switch (c) {
	case '+':
		return SET;
	case '-':
		return UNSET;
	default:
		return SET_ERR;
	}
}

/* Returns one of the following: B, C, D, TYPE_ERR */
e_mdetype check::mode_::typeIsValid(const char &c) {
	switch (c) {
	case 'i':
		return D;
	case 'k':
		return C;
	case 'l':
		return C;
	case 'o':
		return B;
	case 't':
		return D;
	default:
		return TYPE_ERR;
	}
}

/* for the current flag, recover type of setchar [+ | -] and type of flagtype [i
| k | l | o | t] Sends the ERR_UNKNOWN PARAM if they don't exist, then return an
error. Returns an error if they don't exist */
bool check::mode_::validFlag(e_mdeset &set, e_mdetype &type,
							 const std::string &flag, const Client &cli) {
	try {
		set = check::mode_::whichSet(flag.at(0));
		type = check::mode_::typeIsValid(flag.at(1));
	} catch (std::exception &e) { return false; }
	if (!set || !type) {
		reply::send_(cli.getFd(),
					 ERR_UNKNOWNMODE(cli.cliInfo.getNick(),
									 (!set ? flag.at(0) : flag.at(1))));
		return false;
	}
	return true;
}

// if we MUST have a param and we don't, erase the flag
// else if we don't need a parameter, and cmd[flagArg_] is empty, we add a blank space at str.begin()
// else if we don't need a parameter, and cmd[flagArg_] is not empty, we add a blank space at i
// increment if no cmd[flag_] were removed
/* formats mode arguments, validating that each flag is paired with an
 * argument*/

bool check::mode_::formatArgs(CmdSpec &cmd) {
	e_mdetype type;
	e_mdeset set;

	if (cmd[flag_].empty()) {
		return true;
	}
	size_t size;
	for (size_t i = 0; i < cmd[flag_].size();) {
		size = cmd[flag_].size();
		if (!check::mode_::validFlag(set, type, cmd[flag_][i], cmd.getSender()))
			return false;

		const bool needArg = ((type == B) || (type == C && set == SET));
		const bool needEmpty = ((type == D) || (type == C && set == UNSET));

		if (needArg && i >= cmd[flagArg_].size())
			cmd[flag_].rmParam(i);
		else if (needEmpty) {
			cmd[flagArg_].addOne(i);
		}
		if (size == cmd[flag_].size())
			i++;
	}
	print::modeArgs(cmd[flag_].getInnerParam(), cmd[flagArg_].getInnerParam(),
					"After formatting");
	if (cmd[flag_].empty()) {
		reply::send_(cmd.getSdFd(),
					 ERR_NEEDMOREPARAMS(cmd.getSdNick(), cmd.getName()));
		return false;
	}
	return true;
}

bool check::mode_::oTargetIsOnChan(const CmdSpec &cmd, size_t idx) {
	stringVec tChan;
	if (!check::exists(cmd[flagArg_][idx], cmd.serv_.getUsedNick())) {
		reply::send_(cmd.getSdFd(),
					 ERR_NOSUCHNICK(cmd.getSdNick(), cmd[channel_][0]));
		return false;
	}
	tChan = check::getTargetChan(cmd[flagArg_][idx], cmd.serv_);
	if (!check::chans_::onChan(cmd[channel_][idx], tChan)) {
		reply::send_(cmd.getSdFd(),
					 ERR_USERNOTINCHANNEL(cmd.getSdNick(), cmd[flag_][idx],
										  cmd[channel_][0]));
		return false;
	}
	return true;
}

bool check::mode(CmdSpec &cmd, size_t idx) {
	(void)idx;
	if (!check::mode_::formatArgs(cmd))
		return false;

	for (; idx < cmd[flag_].size(); ++idx) {
		std::cout << idx << " | "
				  << cmd[flag_][idx] + " | " + cmd[flagArg_][idx] << std::endl;
		if (cmd[flag_][idx] == "+o") {
			if (!check::mode_::oTargetIsOnChan(cmd, idx))
				return false;
		}
		if (cmd[flag_][idx] == "+k") {
			if (cmd[flagArg_][idx].size() < 8 ||
				cmd[flagArg_][idx].size() > 26) {
				reply::send_(cmd.getSdFd(),
							 "Key should be between 8 and 26 char long");
				return false;
			}
		}
	}
	return true;
}

// TODO: +l: block if arg is not an interger
