/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Director.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:25:38 by csweetin          #+#    #+#             */
/*   Updated: 2025/02/26 17:24:38 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Director.hpp"

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */

Director::Director(void) {}

Director::Director(const Director &rhs)
{
	*this = rhs;
}

Director::~Director(void) {}

Director &Director::operator=(const Director &rhs)
{
	// rhs instructions
	return *this;
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */
	
void	Director::buildCommands()
{
	/*

	CmBuilder	Join = CmBuilder::builder()
							.setName("join")
							.requirement(3)
							.addParam(CmParam::builder(channel)
											.validChan()
							.addParam(CmParam::builder(string of channel), optionnal)
							.addParam(CmParam::builder(string of keys), optionnal)
							.joinChanRequest()
							.enoughParam())
							.addExecutor(*addToChan())
							.build()

	register(Join);

	CmBuilder	Invite = CmBuilder::builder()
								.setName("invite")
								.requirement(3)
								.addParam(CmParam::builder(nickname)
								.addParam(CmParam::builder(channel)
											.validChan())
								.enoughParam()
								.onChan()
								if invite-only mode
									.hasChanPriv()
								.validInvite()
								.addExecutor(*inviteUser())
								.build()

	register(Invite);

	CmBuilder	Kick = CmBuilder::builder()
							.setName("kick")
							.requirement(3)
							.addParam(CmParam::builder(channel)
										.validChan())
							.addParam(CmParam::builder(user))
							.enoughParam()
							.addParam(CmParam::builder(string of users), optionnal)
							.addParam(CmParam::builder(comment), optionnal)
							.onChan()
							.hasChanPriv()
							.validKick()
							.addExecutor(*kickUser())
							.build()

	register(Kick);

	CmBuilder	Mode = CmBuilder::builder()
							.setName("mode")
							.requirement(3)
							.hasChanPriv()
							.addParam(CmParam::builder(channel)
										.validChan())
							.addParam(CmParam::builder(string of modes), optionnal)
							.addParam(CmParam::builder(string of mode args), optionnal)
							.addExecutor(*changeMode())
							.build()

	register(Mode);

	CmBuilder	Nick = CmBuilder::builder()
							.setName("nick")
							.requirement(1)
							.addParam(CmParam::builder(nickname)
							.validNick()
							.addExecutor(*setNick())
							.build()

	register(Nick);

	CmBuilder	Oper = CmBuilder::builder()
								.setName("oper")
								.requirement(3)
								.addParam(CmParam::builder(user)
												.clientAuth())
								.addParam(CmParam::builder(password)
												.pwMatch())
								.enoughParam()
								.addExecutor(*setOper())
								.build()

	register(Oper);

	CmBuilder	Part = CmBuilder::builder()
								.setName("part")
								.requirement(3)
								.addParam(CmParam::builder(channel)
											.validChan())
								.addParam(CmParam::builder(string of channels), optionnal)
											.validChan())
								.addParam(CmParam::builder(reason), optionnal)
								.enoughParam()
								.onChan()
								.addExecutor(*rmFromChan())
								.build()

	register(Part);

	CmBuilder	Pass = CmBuilder::builder()
								.setName("pass")
								.requirement(0)
								.addParam(CmParam::builder(password)
											.pwMatch())
								.enoughParam()
								.addExecutor(*setPw())
								.build()

	register(Pass);

	CmBuilder	Privmsg = CmBuilder::builder()
								.setName("privmsg")
								.requirement(3)
								.addParam(CmParam::builder(receiver))
								.addParam(CmParam::builder(string of receivers), optionnal)
											.validChan())
								.addParam(CmParam::builder(text to be sent))
								.enoughParam()
								.validMess()
								.addExecutor(*sendMess())
								.build()

	register(Privmsg);

	CmBuilder	Quit = CmBuilder::builder()
								.setName("quit")
								.requirement(3)
								.addParam(CmParam::builder(quit message), optionnal)
								.addExecutor(*cutConnexion())
								.build()

	register(Quit);

	CmBuilder	Topic = CmBuilder::builder()
								.setName("topic")
								.requirement(3)
								.addParam(CmParam::builder(channel))
											.validChan())
								.addParam(CmParam::builder(topic), optionnal)
								.enoughParam()
								.onChan()
								if mode +t is set
									.hasChanPriv()
								.addExecutor(*changeTopic())
								.build()

	register(Topic);

	CmBuilder	User = CmBuilder::builder()
								.setName("user")
								.requirement(2)
								.addParam(CmParam::builder(username))
											.validUser()
								.addParam(CmParam::builder(realname))
								.enoughParam()
								.addExecutor(*setUser())
								.build()

	register(User);

	*/
}