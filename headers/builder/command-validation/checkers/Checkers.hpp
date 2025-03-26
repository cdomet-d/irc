/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Checkers.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:49:12 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/26 14:21:20 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKERS_HPP
#define CHECKERS_HPP
#define CHECKERS_HPP

#include "CmdSpec.hpp"
class CmdSpec;

bool privileges(CmdSpec &cmd);		// Charlotte
bool isRegistered(CmdSpec &cmd);	// Charlotte
bool assessRequest(CmdSpec &cmd); // Charlotte
bool onChan(CmdSpec &cmd);			// Charlotte
bool pwMatch(CmdSpec &cmd);			// Charlotte
bool RegStageDone(CmdSpec &cmd);	// Charlotte


#endif