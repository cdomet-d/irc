//HEADER

#ifndef COMMANDMANAGER_HPP
# define COMMANDMANAGER_HPP

# include <iostream>
# include <map>
# include "CommandResult.hpp"
# include "CommandSpec.hpp"

class	CommandManager
{
	private:
		// std::map<std::string, CommandResult>	commandList;
		std::map<std::string, CommandSpec>	commandList;
	public:
		//constructors & destructor
		CommandManager(void);
		CommandManager(const CommandManager& obj);
		~CommandManager(void);

		//operators
		CommandManager&	operator=(const CommandManager& obj);

		//methods
		void			generateCmds();
		// CommandResult&	getCmd(const std::string& cmName);
		CommandSpec&	getCmd(const std::string& cmName);
		// void			executeCm(CommandResult& cm);
		void			executeCm(CommandSpec& cm);
		void			log(CommandSpec& cm);
};

#endif
