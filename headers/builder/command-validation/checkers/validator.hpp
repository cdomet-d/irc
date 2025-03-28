/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:58:30 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/28 16:41:08 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include "CmdSpec.hpp"

namespace check {
	bool chan(CmdSpec &cmd);
	bool invite(CmdSpec &cmd);
	bool kick(CmdSpec &cmd);
	bool mess(CmdSpec &cmd);
	bool mode(CmdSpec &cmd);
	bool nick(CmdSpec &cmd);
	bool target(CmdSpec &cmd);
	bool user(CmdSpec &cmd);
	bool join(CmdSpec &cmd);

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
		bool isOnChan(CmdSpec &cmd);
		bool hasChanAuthorisations(CmdSpec &cmd);
	} // namespace chans_
	namespace register_ {
		bool isRegistered(CmdSpec &cmd);
		bool stageDone(CmdSpec &cmd);
		bool pwMatch(CmdSpec &cmd);
	} // namespace register_
} // namespace check

#endif