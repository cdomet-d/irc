/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:58:30 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/28 18:25:15 by csweetin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include "CmdSpec.hpp"
#include <algorithm>

namespace check {
	bool chan(CmdSpec &cmd, size_t idx);
	bool invite(CmdSpec &cmd, size_t idx);
	bool kick(CmdSpec &cmd, size_t idx);
	bool part(CmdSpec &cmd, size_t idx);
	bool mess(CmdSpec &cmd, size_t idx);
	bool mode(CmdSpec &cmd, size_t idx);
	bool nick(CmdSpec &cmd, size_t idx);
	bool target(CmdSpec &cmd, size_t idx);
	bool user(CmdSpec &cmd, size_t idx);
	bool join(CmdSpec &cmd, size_t idx);
	bool enoughParams(CmdSpec &cmd, size_t idx);
	bool len(CmdSpec &cmd, size_t idx);
	const stringVec &getTargetChan(const std::string &target,
								   const Server &serv);
	template < typename MapType >
	bool exists(const std::string &arg, const MapType &map) {
		typename MapType::const_iterator toFind = map.find(arg);
		return toFind != map.end();
	}

	namespace mode_ {
		bool formatArgs(CmdSpec &cmd);
		bool validFlag(e_mdeset &set, e_mdetype &type, const std::string &flag,
					   const Client &cli);
		e_mdeset whichSet(const char &c);
		e_mdetype typeIsValid(const char &c);
		bool oTargetIsOnChan(const CmdSpec &cmd, size_t idx);
		bool lArgIsDigit(const CmdSpec &cmd, size_t idx);
	} // namespace mode_

	namespace nick_ {
		bool isAllowed(const char &c);
		bool isSpecial(const char &c);
		int syntaxIsValid(const std::string &nick);
		std::string createErrorMess(const std::string &nick, int rv);
	} // namespace nick_

	namespace join_ {
		bool assessRequest(const Channel &chan, CmdSpec &cmd, size_t i);
		bool hasInvite(const Channel &chan, Client &sender);
		bool validKey(const Channel &chan, CmdParam &keys, size_t i,
					  Client &sender);
		bool chanHasRoom(const Channel &chan, Client &sender);
		bool cliHasMaxChans(const CmdSpec &cmd, size_t idx);
		bool chanSyntaxIsValid(const CmdSpec &cmd, size_t idx);
	} // namespace join_

	namespace chans_ {
		bool isOp(CmdSpec &cmd, size_t idx);
		bool onChan(std::string arg, const stringVec &arr);
	} // namespace chans_

	namespace register_ {
		bool isRegistered(CmdSpec &cmd, size_t idx);
		bool stageDone(CmdSpec &cmd, size_t idx);
		bool pwMatch(CmdSpec &cmd, size_t idx);
	} // namespace register_

	namespace mess_ {
		bool params(CmdSpec &cmd);
	} // namespace mess_
} // namespace check

#endif