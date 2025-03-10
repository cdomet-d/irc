/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandSpec.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:13:38 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/10 16:50:06 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDSPEC_HPP
# define COMMANDSPEC_HPP

# include <iostream>
# include "CommandParam.hpp"
// # include "Executor.hpp"
// # include "Join.hpp"
# include <map>

typedef enum	p_enum
{
	password,
	nickname,
	username,
	channel,
	key,
	target
};

class	CommandSpec
{
	private:
		std::string										name_;
		// void(*inputTokenizer_)(std::string& buffer, CommandParam& param);
		int												registrationStage_;
		std::map<p_enum, std::vector<CommandParam*> >	params_;
		// int												minParam_;
		std::vector<void(*)(CommandSpec&)>				checkers_; //faire un template ??
		// Executor*										cmExecutor_;
		void(*cmExecutor_)(CommandSpec& cmd);
		bool											cancelled_;
		Client&											sender;
		
		//constructors
		CommandSpec(void);
		CommandSpec(std::string name, int registrationStage, std::map<p_enum, std::vector<CommandParam*> > params, \
					std::vector<void(*)(CommandSpec&)> checkers, void(*cmExecutor_)(CommandSpec& cmd));
		CommandSpec(const CommandSpec& obj);
	public:
		//destructor
		~CommandSpec(void);

		//operators
		CommandSpec&	operator=(const CommandSpec& obj);
		
		//method
		CommandSpec&	process(std::string& buffer, Client& client);

		//getters
		std::string		getName(void);
		bool			getCancelled(void);
		// Executor*		getExecutor(void);
		
		
		// nested class
		class	CommandBuilder //builds a command
		{
			private:
				std::string										name_;
				int												registrationStage_;
				std::map<p_enum, std::vector<CommandParam*> >	params_;
				std::vector<void(*)(CommandSpec& cmd)>			checkers_; //faire un template ??
				void(*cmExecutor_)(CommandSpec& cmd);
			public:
				//constructors & destructor
				CommandBuilder(void);
				CommandBuilder(const CommandBuilder& obj);
				~CommandBuilder(void);

				//operators
				CommandBuilder&	operator=(const CommandBuilder& obj);

				//methods
				CommandBuilder&	Name(const std::string& name);
				CommandBuilder&	Registration(int stage);
				CommandBuilder&	addChecker(void(*ft)(CommandSpec& cmd));
				// CommandBuilder&	InputTokenizer(void(*ft)(std::string& buffer, CommandParam& param));
				CommandBuilder&	Parameters(CommandParam* param);
				// CommandBuilder&	MinParam(int minParam);
				CommandBuilder&	CmExecutor(void(*ft)(CommandSpec& cmd));
				CommandSpec*	build();
		};
};

void	splitOnComa(std::string& buffer, CommandParam& param);
// void	splitJoin(std::string& buffer, CommandParam& param);
void	splitOnSpace(std::string& buffer, CommandParam& param);

#endif

