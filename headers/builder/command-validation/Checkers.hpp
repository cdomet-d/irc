/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Checkers.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:49:12 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/11 17:19:53 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKERS_HPP
# define CHECKERS_HPP

# include "CmdSpec.hpp"

class CmdSpec;

int	hasChanPriv(CmdSpec& cmd);
int	isRegistered(CmdSpec& cmd);
int	joinChanRequest(CmdSpec& cmd);
int	onChan(CmdSpec& cmd);
int	pwMatch(CmdSpec& cmd);
int	validChan(CmdSpec& cmd);
int	validInvite(CmdSpec& cmd);
int	validKick(CmdSpec& cmd);
int	validMess(CmdSpec& cmd);
int	validMode(CmdSpec& cmd);
int	validNick(CmdSpec& cmd);
int	validTarget(CmdSpec& cmd);
int	validUser(CmdSpec& cmd);

#endif