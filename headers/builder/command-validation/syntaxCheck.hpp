/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxCheck.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:08:10 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/18 16:27:40 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAXCHECK_HPP
#define SYNTAXCHECK_HPP

#include "typedef.hpp"

class CmdSpec;

namespace syntaxCheck {
	namespace nick {
		bool isValid(const std::string &nick, const CmdSpec &cmd);
		std::string trim(const std::string &nick);
		namespace priv {
			bool isValidChar(const char &c);
			bool isSpecial(const char &c);
		} // namespace priv
	} // namespace nick
}; // namespace syntaxCheck

namespace conflictCheck {
	namespace nick {
		bool inUse(const std::string &nick,
								const nickMap &regCli, const int &senderFd);
		namespace priv {}
	} // namespace nick
}; // namespace conflictCheck
#endif