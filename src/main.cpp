#include <iostream>
#include "CommandManager.hpp"

int	main(void)
{
	std::string		buffer = "JOIN #pizza,#bitch,prout key1,key2 other shit";
	CommandManager	cmManager;
	size_t			i = 0;
	std::string		cm;

	//create the map with all registered commands
	cmManager.generateCmds();

	//execute command
	i = buffer.find(" ");
	if (i == std::string::npos)
		i = buffer.size() - 1;
	cm.assign(buffer, i);
	buffer.erase(buffer.begin() + i + 1);
	cmManager.executeCm(cmManager.getCmd(cm).process(buffer));
}