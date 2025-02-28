//HEADER

#ifndef COMMANDSPEC_HPP
# define COMMANDSPEC_HPP

# include <iostream>
# include "CommandResult.hpp"
# include "ParamGenerator.hpp"

class	CommandSpec //builds a command
{
	private:
		CommandResult	cmd;
		std::string		name;
		void(*inputTokenizer)();
		int				registrationStage;	
	public:
		//constructors & destructor
		CommandSpec(void);
		~CommandSpec(void);

		//methods
		CommandSpec&	Name(const std::string& name);
		CommandSpec&	InputTokenizer(void(*ft)());
		CommandSpec&	Registration(int stage);
		CommandSpec&	Parameters(ParamGenerator& params);
		CommandSpec&	build();
		CommandResult&	getCmdResult();
};

void	splitOnComa(void);

#endif
