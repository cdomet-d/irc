/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cmd.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:23:19 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/24 19:23:21 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_HPP
#define CMD_HPP

#include "Bot.hpp"
#include <string>

namespace cmd {
	void acceptInvite(const int fd, const std::string &target);
	void disconnect(Bot &bot);
	bool parseLogin(std::string &login);
	void man(Bot &bot, const std::string &target);
} // namespace cmd

#endif
