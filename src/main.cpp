#include <iostream>
#include "CommandManager.hpp"

int	main(void)
{
	std::string		buffer = "JOIN #pizza,#bitch,prout key1,key2 other shit";
	CommandManager	cmManager;

	//create the map with all registered commands
	cmManager.generateCmds();

	//execute command
	cmManager.execute(cmManager.getCmd("JOIN").process(buffer));
}