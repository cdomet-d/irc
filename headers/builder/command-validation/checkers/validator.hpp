/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:58:30 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/26 14:21:22 by cdomet-d         ###   ########.fr       */
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

	namespace mode_ {
		bool format(CmdSpec &cmd);
		namespace valid {
			bool flag(e_mdeset &set, e_mdetype &type, const std::string &flag,
					  const Client &cli);
			e_mdeset set(const char &c);
			e_mdetype type(const char &c);
		} // namespace check
	} // namespace mode_

	namespace nick_ {
		bool unique(const std::string &nick, const nickMap &regCli,
					const int &senderFd);
		std::string trim(const std::string &nick);
		namespace valid {
			bool alphaNumChar(const char &c);
			bool specialChar(const char &c);
			bool syntax(const std::string &nick, const CmdSpec &cmd);
		}
	} // namespace nick_

	namespace join_ {
		bool hasChanPriv(CmdSpec &cmd);
		bool assessRequest(CmdSpec &cmd);
		namespace valid {
			bool request(Channel chan, CmdSpec &cmd, size_t i);
			bool onChan(CmdSpec &cmd);
			bool hasInvite(Channel &chan, Client &sender);
			bool validKey(Channel &chan, CmdParam &keys, size_t i,
						  Client &sender);
			bool reachedChanLimit(Channel &chan, Client &sender);
			bool reachedCliChanLimit(Channel &chan, Client &sender);
		} // namespace check
	} // namespace join_
} // namespace check

#endif