/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 09:04:38 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/15 11:54:08 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdExecution.hpp"
#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "Server.hpp"

void pass(CmdSpec &cmd) {
	Client *sender = &cmd.getSender();
	RPL::send_(sender->getFd(), PASS_SUCCESS(cmd.getSdNick()));
	sender->cliInfo.setRegistration(1);
}
