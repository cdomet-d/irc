/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:20:57 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/20 13:52:47 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "Server.hpp"

void nick(CmdSpec &cmd) {
	Client *sender = &cmd.getSender();
	sender->cliInfo.setNick(cmd[nickname_][0]);
	sender->cliInfo.setRegistration(2);
}
