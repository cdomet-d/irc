/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdExecution.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlotte <charlotte@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:08:25 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/31 09:40:04 by charlotte        ###   ########.fr       */
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

//UTILS
Channel &findCurChan(std::string chanName);
Channel *createChan(const std::string &chanName);
void checkOnlyOperator(Channel *curChan);
void partOneChan(Client *sender, Channel &curChan);
void partAllChans(Client *sender);

#endif ///CMDEXECUTION_HPP