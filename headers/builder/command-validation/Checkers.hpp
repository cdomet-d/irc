/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Checkers.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:49:12 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/19 15:43:09 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKERS_HPP
#define CHECKERS_HPP

#include "CmdSpec.hpp"
#include "Channel.hpp"
class CmdSpec;

bool hasChanPriv(CmdSpec &cmd);		// Charlotte
bool isRegistered(CmdSpec &cmd);	// Charlotte
bool joinChanRequest(CmdSpec &cmd); // Charlotte
bool onChan(CmdSpec &cmd);			// Charlotte
bool pwMatch(CmdSpec &cmd);			// Charlotte
bool validChan(CmdSpec &cmd);		// Coralie
bool validInvite(CmdSpec &cmd);		// Coralie
bool validKick(CmdSpec &cmd);		// Coralie
bool validMess(CmdSpec &cmd);		// Coralie
bool validMode(CmdSpec &cmd);		// Coralie
bool validNick(CmdSpec &cmd);		// Coralie
bool validTarget(CmdSpec &cmd);		// Coralie
bool validUser(CmdSpec &cmd);		// Coralie

// namespace joinChecker {
// 	bool reachedChanLimit(Channel &chan);
// 	bool hasInvite(Channel &chan, Client &sender);
// 	bool hasKey(Channel &chan, CmdParam &keys, size_t i);
// 	bool reachedCliChanLimit(Client &sender);
// };

#endif