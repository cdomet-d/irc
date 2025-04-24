/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:12:52 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/24 14:57:02 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Exceptions.hpp"
#include "Reply.hpp"
#include "Server.hpp"

void part(CmdSpec &cmd) {
	Client &sender = cmd.getSender();
	std::string message;
	if (!cmd[message_].empty())
		message = cmd[message_][0];

	for (size_t nbChan = 0; nbChan < cmd[channel_].size(); nbChan++) {
		try {
			Channel &curChan = cmd.serv_.findChan(cmd[channel_][nbChan]);
			curChan.partMess(sender, curChan, message);
			curChan.partOneChan(sender, curChan);
			curChan.checkOnlyOperator(sender);
		} catch (ObjectNotFound &e) { RPL::log(RPL::ERROR, e.what()); }
	}
}
