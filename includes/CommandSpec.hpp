//HEADER

#ifndef COMMANDSPEC_HPP
# define COMMANDSPEC_HPP

# include <iostream>
# include "CommandResult.hpp"
# include "ParamGenerator.hpp"
# include "Executor.hpp"
# include "Join.hpp"
# include "Client.hpp"

class	CommandSpec //builds a command
{
	private:
		// CommandResult			cmd;
		std::string				name;
		void(*inputTokenizer)(std::string& buffer, CommandParam& param);
		int						registrationStage;
		ParamGenerator			params;
		int						minParam;
		std::vector<void(*)()>	issuerChecks;
		Executor*				cmExecutor;
	public:
		//constructors & destructor
		CommandSpec(void);
		~CommandSpec(void);

		//methods
		CommandSpec&	Name(const std::string& name);
		CommandSpec&	Registration(int stage);
		CommandSpec&	IssuerChecks(void(*ft)());
		CommandSpec&	InputTokenizer(void(*ft)(std::string& buffer, CommandParam& param));
		CommandSpec&	Parameters(ParamGenerator& params);
		CommandSpec&	MinParam(int minParam);
		CommandSpec&	CmExecutor(Executor* cmExecutor);
		CommandSpec&	build();
		// CommandResult&	getCmdResult();
		CommandSpec&	process(std::string& buffer, Client& client);

		//getters
		std::string&	getName(void);
		ParamGenerator&	getParamGenerator(void){
			return (this->params);}
		void	(*getInputTokenizer())(std::string& buffer, CommandParam& param){
			return (this->inputTokenizer);
		}
};

void	splitOnComa(std::string& buffer, CommandParam& param);

#endif
