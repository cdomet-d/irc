/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_mode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:58:28 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/26 14:17:48 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.hpp"

/* Returns SET, UNSER or SET_ERR */
e_mdeset check::mode_::valid::set(const char &c) {
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
e_mdetype check::mode_::valid::type(const char &c) {
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
bool check::mode_::valid::flag(e_mdeset &set, e_mdetype &type,
							   const std::string &flag, const Client &cli) {
	try {
		set = check::mode_::valid::set(flag.at(0));
		type = check::mode_::type(flag.at(1));
	} catch (std::exception &e) { return false; }
	if (!set || !type) {
		reply::send(cli.getFd(),
					ERR_UNKNOWNMODE(cli.cliInfo.getNick(),
									(!set ? flag.at(0) : flag.at(1))));
		return false;
	}
	return true;
}

/* formats mode arguments, validating that each flag is paired with an argument*/
bool check::mode_::format(CmdSpec &cmd) {
	e_mdetype type;
	e_mdeset set;
	stringVec flags, param;

	if (cmd[flag_].empty()) {
		return true;
	}
	size_t size;
	for (size_t i = 0; i < cmd[flag_].size();) {
		size = cmd[flag_].size();
		if (!check::mode_::flag(set, type, cmd[flag_][i], cmd.getSender()))
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
		reply::send(
			cmd.getSender().getFd(),
			ERR_NEEDMOREPARAMS(cmd.getSender().cliInfo.getNick(), "Mode"));
		return false;
	}
	return true;
}

bool check::mode(CmdSpec &cmd) {
	if (!check::mode_::format(cmd))
		return false;
}