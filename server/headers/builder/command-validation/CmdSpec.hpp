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

#include "CmdParam.hpp"
#include "Server.hpp"
#include <iostream>
#include <map>
#include <utility>
#include <vector>

class Client;

typedef enum {
	channel_,
	hostname_,
	key_,
	message_,
	flag_,
	flagArg_,
	nickname_,
	password_,
	realname_,
	servername_,
	target_,
	topic_,
	username_,
} e_param;

typedef std::vector< std::pair< e_param, CmdParam * > > paramMap;

class CmdSpec {
  public:
	/*                               CONSTRUCTORS                             */
	~CmdSpec();

	/*                               MEMBERS                                  */
	Server &serv_;

	/*                               METHODS                                  */
	CmdParam &operator[](e_param type);
	const CmdParam &operator[](e_param type) const;
	CmdSpec &process(Client &sender);
	void cleanAll();
	bool checkRegistrationStage();

	void displayParams(const std::string &where); // to be removed

	/*                               GETTERS                                  */
	bool getValid() const;
	Client &getSender() const;
	const std::string getSdNick() const;
	const std::string getSdPre() const;
	int getSdFd() const;
	const paramMap &getParams() const;
	const std::string &getName() const;
	int getRegistrationStage() const;
	void (*getExecutor() const)(CmdSpec &cmd);

	/*                               SETTERS                                  */
	void setSender(Client &sender);
	void setParam();
	void hasParamList();

	/*                               NESTED CLASS                             */
	class CmdBuilder {
	  public:
		CmdBuilder();
		~CmdBuilder();

		// methods
		CmdBuilder &addChecker(bool (*ft)(CmdSpec &cmd, size_t idx));
		CmdBuilder &CmExecutor(void (*ft)(CmdSpec &cmd));
		CmdBuilder &Name(const std::string &name);
		CmdBuilder &addParam(e_param type, CmdParam *param);
		CmdBuilder &Registration(int stage);
		CmdSpec *build();

	  private:
		int registrationStage_;
		paramMap params_;
		std::string name_;
		std::vector< bool (*)(CmdSpec &cmd, size_t idx) > checkers_;
		void (*cmExecutor_)(CmdSpec &cmd);
	};

  private:
	/*                               MEMBERS                                  */
	bool valid_;
	Client *sender_;
	const std::string name_;
	int registrationStage_;
	paramMap params_;
	std::vector< bool (*)(CmdSpec &cmd, size_t idx) > checkers_;
	void (*cmExecutor_)(CmdSpec &cmd);

	// private constructor
	CmdSpec(const std::string name, int registrationStage, paramMap params,
			std::vector< bool (*)(CmdSpec &, size_t) > checkers,
			void (*cmExecutor)(CmdSpec &cmd));
};

#endif
