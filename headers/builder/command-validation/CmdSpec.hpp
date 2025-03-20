/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdSpec.hpp                                    	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:13:38 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/10 17:27:00 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDSPEC_HPP
#define CMDSPEC_HPP

#include "Checkers.hpp"
#include "CmdParam.hpp"
#include "Server.hpp"
#include <iostream>
#include <map>
#include <utility>
#include <vector>

class Client;

typedef enum {
	channel,
	hostname,
	key,
	message,
	mode_,
	modeArg,
	nickname,
	password,
	realname,
	servername,
	target,
	topic_,
	username,
} e_param;

typedef std::vector< std::pair< e_param, CmdParam * > > paramMap;

class CmdSpec {
  public:
	/*                               CONSTRUCTORS                             */
	~CmdSpec(void);

	/*                               MEMBERS                                  */
	Server &server_;

	/*                               METHODS                                  */
	CmdParam &operator[](e_param type);
	CmdSpec &process(Client &sender);
	bool enoughParams(void);
	void cleanAll(void);

	void displayParams(void); //to be removed

	/*                               GETTERS                                  */
	bool getValid(void) const;
	Client &getSender(void) const;
	const std::string &getName(void) const;
	const paramMap &getParams(void) const;
	void (*getExecutor(void) const)(CmdSpec &cmd);

	/*                               SETTERS                                  */
	void setSender(Client &sender);
	void setValid(bool valid);

	/*                               NESTED CLASS                             */
	class CmdBuilder {
	  public:
		CmdBuilder(void);
		~CmdBuilder(void);

		//methods
		CmdBuilder &addChecker(int (*ft)(CmdSpec &cmd));
		CmdBuilder &CmExecutor(void (*ft)(CmdSpec &cmd));
		CmdBuilder &Name(const std::string &name);
		CmdBuilder &Parameters(e_param type, CmdParam *param);
		CmdBuilder &Registration(int stage);
		CmdSpec *build();

	  private:
		int registrationStage_;
		paramMap params_;
		std::string name_;
		std::vector< int (*)(CmdSpec &cmd) > checkers_;
		void (*cmExecutor_)(CmdSpec &cmd);
	};

  private:
	/*                               MEMBERS                                  */
	bool valid_;
	Client *sender_;
	const std::string name_;
	int registrationStage_;
	paramMap params_;
	std::vector< int (*)(CmdSpec &cmd) > checkers_;
	void (*cmExecutor_)(CmdSpec &cmd);

	// private constructor
	CmdSpec(const std::string name, int registrationStage, paramMap params,
			std::vector< int (*)(CmdSpec &) > checkers,
			void (*cmExecutor)(CmdSpec &cmd));
};

//JOIN
void joinExec(CmdSpec &cmd);
Channel *createChan(const std::string &chanName);

//MODE
void modeExec(CmdSpec &cmd);
typedef void (*modesFunc)(std::string flag, std::string param, Channel &curChan);

//TOPIC
void topicExec(CmdSpec &cmd);

//INVITE
void inviteExec(CmdSpec &cmd);

//KICK
void kickExec(CmdSpec &cmd);

//PART
void partExec(CmdSpec &cmd);

//PRIVMSG
void privmsgExec(CmdSpec &cmd);

//UTILS
Channel &findCurChan(std::string chanName);

#endif
