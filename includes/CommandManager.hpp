//HEADER

#ifndef COMMANDMANAGER_HPP
# define COMMANDMANAGER_HPP

# include <iostream>
# include <map>
# include "CommandResult.hpp"

class	CommandManager
{
	private:
		std::map<std::string, CommandResult>	commandList;
	public:
		//constructors & destructor
		CommandManager(void);
		CommandManager(const CommandManager& obj);
		~CommandManager(void);

		//operators
		CommandManager&	operator=(const CommandManager& obj);

		//methods
		void			generateCmds();
		CommandResult&	getCmd(const std::string& cmName);
		void			execute(CommandResult& cm);
};

#endif
