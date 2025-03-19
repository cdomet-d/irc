/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Checkers.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:15:18 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/18 17:00:49 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Checkers.hpp"

int pwMatch(CmdSpec &cmd)
{
	(void)cmd;
	return (0);
}

int isRegistered(CmdSpec &cmd)
{
	(void)cmd;
	return (0);
}

int validNick(CmdSpec &cmd)
{
	(void)cmd;
	return (0);
}

int validUser(CmdSpec &cmd)
{
	(void)cmd;
	return (0);
}

int validChan(CmdSpec &cmd)
{
	(void)cmd;
	return (0);
}

int joinChanRequest(CmdSpec &cmd)
{
	for (size_t i = 0; i < cmd[channel].getSize(); i++)
		if (cmd[channel][i][0] != '#') {
			std::cout << ERR_NOSUCHCHANNEL(cmd.getSender().cliInfo.getNick(),
										   cmd[channel][i]);
		}
	//supprimer chaque channel faux, (ainsi que toutes les keys ? peut etre pas necessaire)
	//pour qu'il reste que les channel valide a join pour l'exec
	//s'ils ont tous ete supprimes mettre valid a false
	return (0);
}

int validTarget(CmdSpec &cmd)
{
	(void)cmd;
	return (0);
}

int validInvite(CmdSpec &cmd)
{
	(void)cmd;
	return (0);
}

int onChan(CmdSpec &cmd)
{
	(void)cmd;
	return (0);
}

int hasChanPriv(CmdSpec &cmd)
{
	(void)cmd;
	return (0);
}

int validKick(CmdSpec &cmd)
{
	(void)cmd;
	return (0);
}

int validMode(CmdSpec &cmd)
{
	(void)cmd;
	return (0);
}

int validMess(CmdSpec &cmd)
{
	(void)cmd;
	return (0);
}
