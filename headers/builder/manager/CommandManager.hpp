//HEADER

#ifndef COMMANDMANAGER_HPP
#define COMMANDMANAGER_HPP

#include "CommandSpec.hpp"
#include <iostream>
#include <map>

class CommandManager {
  private:
	std::map< std::string, CommandSpec * > commandList;

  public:
	//constructors & destructor
	CommandManager(void);
	CommandManager(const CommandManager &rhs);
	~CommandManager(void);

	//operators
	CommandManager &operator=(const CommandManager &rhs);

	//methods
	void generateCmds();
	CommandSpec &getCmd(const std::string &cmName);
	void executeCm(CommandSpec &cm);
	void log(CommandSpec *cm);
};

#endif
