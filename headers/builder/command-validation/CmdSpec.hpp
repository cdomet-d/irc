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
#include <iostream>
#include <map>
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

typedef std::map< e_param, CmdParam * > paramMap;

class CmdSpec {
  public:
	/*                               CONSTRUCTORS                             */
	~CmdSpec(void);

	/*                               METHODS                                  */
	CmdParam &operator[](e_param type);
	CmdSpec &process(std::vector< std::string > &buffer, Client &client);
	void clean(void);

	/*                               GETTERS                                  */
	//TODO: replace cancelled with valid
	bool getCancelled(void);
	const std::string &getName(void) const;
	void (*getExecutor(void))(CmdSpec &cmd);

	/*                               SETTERS                                  */
	void setSender(Client &sender);

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
	bool cancelled_;
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

#endif
