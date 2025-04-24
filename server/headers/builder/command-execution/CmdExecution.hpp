/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdExecution.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:08:25 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/24 14:52:56 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDEXECUTION_HPP
#define CMDEXECUTION_HPP

#include "CmdSpec.hpp"
#include "typedef.hpp"

typedef void (*modesFunc)(std::string flag, std::string param,
						  Channel &curChan);

void pass(CmdSpec &cmd);
void nick(CmdSpec &cmd);
void user(CmdSpec &cmd);
void join(CmdSpec &cmd);
void who(CmdSpec &cmd);
void mode(CmdSpec &cmd);
void topic(CmdSpec &cmd);
void invite(CmdSpec &cmd);
void kick(CmdSpec &cmd);
void part(CmdSpec &cmd);
void privmsg(CmdSpec &cmd);
void quit(CmdSpec &cmd);
void ping(CmdSpec &cmd);

#endif /// CMDEXECUTION_HPP