//HEADER

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
		std::vector<CommandParam>	params;
		int							minParam;
		std::vector<void(*)()>		issuerChecks;
		Executor*					cmExecutor;
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
				CommandBuilder(const CommandSpec& obj);
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

#endif



