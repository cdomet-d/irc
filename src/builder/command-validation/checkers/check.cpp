/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:15:18 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/27 13:21:29 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Reply.hpp"
#include "validator.hpp"


bool check::chan(CmdSpec &cmd) {
	stringVec param = cmd[channel_].getInnerParam();
	return (true);
}

bool check::user(CmdSpec &cmd) {
	(void)cmd;
	return (true);
}

bool check::target(CmdSpec &cmd) {
	(void)cmd;
	return (true);
}

bool check::invite(CmdSpec &cmd) {
	(void)cmd;
	return (true);
}

bool check::kick(CmdSpec &cmd) {
	(void)cmd;
	return (true);
}

bool check::mess(CmdSpec &cmd) {
	(void)cmd;
	return (true);
}
