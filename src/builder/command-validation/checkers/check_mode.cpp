/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:58:28 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/09 13:40:37 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.hpp"

/* Returns SET, UNSER or SET_ERR */
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

/* for the current flag, recover type of setchar [+ | -] and type of flagtype [i | k | l | o | t]
Sends the ERR_UNKNOWN PARAM if they don't exist, then return an error.
if returns an error if they don't exist */
bool check::mode_::flagIsValid(e_mdeset &set, e_mdetype &type,
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

/* formats mode arguments, validating that each flag is paired with an argument*/
bool check::mode_::formatArgs(CmdSpec &cmd) {
	e_mdetype type;
	e_mdeset set;
	stringVec flags, param;

	if (cmd[flag_].empty()) {
		return true;
	}
	size_t size;
	for (size_t i = 0; i < cmd[flag_].size();) {
		size = cmd[flag_].size();
		if (!check::mode_::flagIsValid(set, type, cmd[flag_][i],
									   cmd.getSender()))
			return false;
		// if we MUST have a param and we don't, erase the flag
		if (((type == B) || (type == C && set == SET)) &&
			i >= cmd[flagArg_].size())
			cmd[flag_].rmParam(i);
		// else if we don't need a parameter, and cmd[flagArg_] is empty, we add a blank space at str.begin()
		else if (cmd[flagArg_].empty() &&
				 ((type == C && set == UNSET) || type == D))
			cmd[flagArg_].addOne(i);
		// else if we don't need a parameter, and cmd[flagArg_] is not, we add a blank space at i
		else if ((type == C && set == UNSET) || type == D)
			cmd[flagArg_].addOne(i);
		// increment if no cmd[flag_] were removed
		if (size == cmd[flag_].size())
			i++;
	}
	if (cmd[flag_].empty()) {
		reply::send_(
			cmd.getSendFd(),
			ERR_NEEDMOREPARAMS(cmd.getSendNick(), "Mode"));
		return false;
	}
	return true;
}

bool check::mode(CmdSpec &cmd, size_t idx) {
	(void)idx;
	if (!check::mode_::formatArgs(cmd))
		return false;
	return true;
}

//TODO: check if there is a target and that the client is on it.
//TODO: +l: block if arg is not an interger
//TODO: +o: check client exist and is on channel
//TODO: +k: check that 26 > len > 8 