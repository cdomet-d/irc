/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandSpec.hpp                                    :+:      :+:    :+:   */
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
# include "CommandParam.hpp"
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

class	CommandSpec
{
	private:
		std::string								name_;
		int										registrationStage_;
		std::map<p_enum, CommandParam*>			params_;
		std::vector<int(*)(CommandSpec&)>		checkers_;
		void(*cmExecutor_)(CommandSpec& cmd);
		bool									cancelled_;
		Client*									sender_;
		
		//constructor
		CommandSpec(std::string name, int registrationStage, std::map<p_enum, CommandParam*> params, \
					std::vector<int(*)(CommandSpec&)> checkers, void(*cmExecutor)(CommandSpec& cmd));
	public:
		//destructor
		~CommandSpec(void);

		//operators
		CommandParam&	operator[](p_enum type);	

		//method
		CommandSpec&	process(std::string& buffer, Client& client);

		//getters
		std::string		getName(void);
		bool			getCancelled(void);
		void			(*getExecutor(void))(CommandSpec& cmd);
		
		//setters
		void			setSender(Client& sender);

		// nested class --------------------------------------------------------
		class	CommandBuilder //builds a command
		{
			private:
				std::string										name_;
				int												registrationStage_;
				std::map<p_enum, CommandParam*>	params_;
				std::vector<int(*)(CommandSpec& cmd)>			checkers_;
				void(*cmExecutor_)(CommandSpec& cmd);
			public:
				//constructors & destructor
				CommandBuilder(void);
				~CommandBuilder(void);

				//methods
				CommandBuilder&	Name(const std::string& name);
				CommandBuilder&	Registration(int stage);
				CommandBuilder&	Parameters(p_enum type, CommandParam* param);
				CommandBuilder&	addChecker(int(*ft)(CommandSpec& cmd));
				CommandBuilder&	CmExecutor(void(*ft)(CommandSpec& cmd));
				CommandSpec*	build();
		};
};

#endif

