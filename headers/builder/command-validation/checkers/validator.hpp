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

namespace check {
	bool chan(CmdSpec &cmd, int idx);
	bool invite(CmdSpec &cmd, int idx);
	bool kick(CmdSpec &cmd, int idx);
	bool part(CmdSpec &cmd, int idx);
	bool mess(CmdSpec &cmd, int idx);
	bool mode(CmdSpec &cmd, int idx);
	bool nick(CmdSpec &cmd, int idx);
	bool target(CmdSpec &cmd, int idx);
	bool user(CmdSpec &cmd, int idx);
	bool join(CmdSpec &cmd, int idx);
	bool enoughParams(CmdSpec &cmd, int idx);
	bool findString(stringVec array, std::string &strToFind);

	namespace mode_ {
		bool formatArgs(CmdSpec &cmd);
		bool flagIsValid(e_mdeset &set, e_mdetype &type,
						 const std::string &flag, const Client &cli);
		e_mdeset whichSet(const char &c);
		e_mdetype typeIsValid(const char &c);
	} // namespace mode_

	namespace nick_ {
		bool isUnique(const std::string &nick, const nickMap &regCli,
					  const int &senderFd);
		std::string trim(const std::string &nick);
		bool isAllowed(const char &c);
		bool isSpecial(const char &c);
		bool syntaxIsValid(const std::string &nick, const int &senderFd);
	} // namespace nick_

	namespace join_ {
		bool assessRequest(Channel chan, CmdSpec &cmd, size_t i);
		bool hasInvite(Channel &chan, Client &sender);
		bool validKey(Channel &chan, CmdParam &keys, size_t i, Client &sender);
		bool chanHasRoom(Channel &chan, Client &sender);
		bool cliHasMaxChans(Channel &chan, Client &sender);
	} // namespace join_

	namespace chans_ {
		bool isOnChan(CmdSpec &cmd, int idx);
		bool hasChanAuthorisations(CmdSpec &cmd, int idx);
	} // namespace chans_
	namespace register_ {
		bool isRegistered(CmdSpec &cmd, int idx);
		bool stageDone(CmdSpec &cmd, int idx);
		bool pwMatch(CmdSpec &cmd, int idx);
	} // namespace register_
} // namespace check

#endif