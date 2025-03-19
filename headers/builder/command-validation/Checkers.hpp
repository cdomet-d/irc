/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Checkers.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:49:12 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/18 16:59:38 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKERS_HPP
#define CHECKERS_HPP

#include "CmdSpec.hpp"

class CmdSpec;

int hasChanPriv(CmdSpec &cmd);	   // Charlotte
int isRegistered(CmdSpec &cmd);	   // Charlotte
int joinChanRequest(CmdSpec &cmd); // Charlotte
int onChan(CmdSpec &cmd);		   // Charlotte
int pwMatch(CmdSpec &cmd);		   // Charlotte
int validChan(CmdSpec &cmd);	   // Coralie
int validInvite(CmdSpec &cmd);	   // Coralie
int validKick(CmdSpec &cmd);	   // Coralie
int validMess(CmdSpec &cmd);	   // Coralie
int validMode(CmdSpec &cmd);	   // Coralie
int validNick(CmdSpec &cmd);	   // Coralie
int validTarget(CmdSpec &cmd);	   // Coralie
int validUser(CmdSpec &cmd);	   // Coralie

#endif