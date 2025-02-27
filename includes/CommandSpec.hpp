//HEADER

#ifndef COMMANDSPEC_HPP
# define COMMANDSPEC_HPP

# include <iostream>
# include "CommandResult.hpp"

class	CommandSpec //builds a command
{
	private:
		CommandResult	cmd;
	public:
		//constructors & destructor
		CommandSpec(void);
		CommandSpec(const CommandSpec& obj);
		~CommandSpec(void);

		//operators
		CommandSpec&	operator=(const CommandSpec& obj);

		//methods
		CommandSpec&	build();
		CommandResult&	getCmdResult();
};

#endif
