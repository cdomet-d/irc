/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandSpec.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:13:38 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/03 17:11:20 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDSPEC_HPP
# define COMMANDSPEC_HPP

# include <iostream>
# include "CommandParam.hpp"
# include "Executor.hpp"
# include "Join.hpp"
# include "Client.hpp"

class	CommandSpec
{
	private:
		std::string					name;
		void(*inputTokenizer)(std::string& buffer, CommandParam& param);
		int							registrationStage;
		std::vector<CommandParam*>	params;
		int							minParam;
		std::vector<void(*)()>		issuerChecks; //faire un template ??
		Executor*					cmExecutor;
		bool						cancelled;
	public:
		//constructors & destructor
		CommandSpec(void);
		CommandSpec(std::string name, void(*inputTokenizer)(std::string& buffer, CommandParam& param), int registrationStage, \
					std::vector<CommandParam*> params, int minParam, std::vector<void(*)()>	issuerChecks, Executor* cmExecutor);
		CommandSpec(const CommandSpec& obj);
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
				std::string					name;
				void(*inputTokenizer)(std::string& buffer, CommandParam& param);
				int							registrationStage;
				std::vector<CommandParam*>	params;
				int							minParam;
				std::vector<void(*)()>		issuerChecks;
				Executor*					cmExecutor;
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
				CommandBuilder&	IssuerChecks(void(*ft)());
				CommandBuilder&	InputTokenizer(void(*ft)(std::string& buffer, CommandParam& param));
				CommandBuilder&	Parameters(CommandParam* param);
				CommandBuilder&	MinParam(int minParam);
				CommandBuilder&	CmExecutor(Executor* cmExecutor);
				CommandSpec*	build();
		};
};

void	splitOnComa(std::string& buffer, CommandParam& param);
void	splitJoin(std::string& buffer, CommandParam& param);

#endif



