/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandSpec.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:13:38 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/07 16:53:56 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDSPEC_HPP
# define COMMANDSPEC_HPP

# include <iostream>
# include "CommandParam.hpp"
# include "Executor.hpp"
# include "Join.hpp"
# include <map>

typedef enum p_enum
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
		void(*inputTokenizer)(std::string& buffer, CommandParam& param);
		std::string									name;
		int											registrationStage;
		std::map<p_enum, std::vector<std::string>>	params;
		int											minParam;
		std::vector<void(*)()>						Checkers; //faire un template ??
		Executor*									cmExecutor;
		bool										cancelled;
		//constructor
		CommandSpec(std::string name, void(*inputTokenizer)(std::string& buffer, CommandParam& param), int registrationStage, \
					std::map<p_enum, std::vector<std::string>> params, int minParam, std::vector<void(*)()> Checkers, \
					Executor* cmExecutor);
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
		Executor*		getExecutor(void);
		
		// nested class
		class	CommandBuilder //builds a command
		{
			private:
				void(*inputTokenizer)(std::string& buffer, CommandParam& param);
				std::string									name;
				int											registrationStage;
				std::map<p_enum, std::vector<std::string>>	params;
				int											minParam;
				std::vector<void(*)()>						Checkers; //faire un template ?
				Executor*									cmExecutor;
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
				CommandBuilder&	Checker(void(*ft)());
				CommandBuilder&	InputTokenizer(void(*ft)(std::string& buffer, CommandParam& param));
				CommandBuilder&	Parameters(CommandParam* param);
				CommandBuilder&	MinParam(int minParam);
				CommandBuilder&	CmExecutor(Executor* cmExecutor);
				CommandSpec*	build();
		};
};

void	splitOnComa(std::string& buffer, CommandParam& param);
// void	splitJoin(std::string& buffer, CommandParam& param);
void	splitOnSpace(std::string& buffer, CommandParam& param);

#endif

