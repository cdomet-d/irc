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

#ifndef COMMANDSPEC_HPP
# define COMMANDSPEC_HPP

# include <iostream>
# include "CmdParam.hpp"
# include <map>
# include "Checkers.hpp"

typedef enum
{
	password,
	nickname,
	username,
	hostname,
	servername,
	realname,
	channel,
	key,
	target,
	message,
	mode_,
	modeArg,
	topic_
}	p_enum;

class	CmdSpec
{
	private:
		std::string							name_;
		int									registrationStage_;
		std::map<p_enum, CmdParam*>			params_;
		std::vector<int(*)(CmdSpec&)>		checkers_;
		void(*cmExecutor_)(CmdSpec& cmd);
		bool								cancelled_;
		Client*								sender_;
		
		//constructor
		CmdSpec(std::string name, int registrationStage, std::map<p_enum, CmdParam*> params, \
					std::vector<int(*)(CmdSpec&)> checkers, void(*cmExecutor)(CmdSpec& cmd));
	public:
		//destructor
		~CmdSpec(void);

		//operators
		CmdParam&	operator[](p_enum type);	

		//method
		CmdSpec&	process(std::string& buffer, Client& client);
		void			clean(void);

		//getters
		std::string		getName(void);
		bool			getCancelled(void);
		void			(*getExecutor(void))(CmdSpec& cmd);
		
		//setters
		void			setSender(Client& sender);

		// nested class --------------------------------------------------------
		class	CommandBuilder //builds a command
		{
			private:
				std::string							name_;
				int									registrationStage_;
				std::map<p_enum, CmdParam*>			params_;
				std::vector<int(*)(CmdSpec& cmd)>	checkers_;
				void(*cmExecutor_)(CmdSpec& cmd);
			public:
				//constructors & destructor
				CommandBuilder(void);
				~CommandBuilder(void);

				//methods
				CommandBuilder&	Name(const std::string& name);
				CommandBuilder&	Registration(int stage);
				CommandBuilder&	Parameters(p_enum type, CmdParam* param);
				CommandBuilder&	addChecker(int(*ft)(CmdSpec& cmd));
				CommandBuilder&	CmExecutor(void(*ft)(CmdSpec& cmd));
				CmdSpec*	build();
		};
};

#endif

