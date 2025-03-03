#include <iostream>
#include "CommandManager.hpp"
#include "Client.hpp"

int	main(int argc, char** argv)
{
	(void)argc;
	Client			client;
	std::string		buffer = "JOIN #pizza,#bitch,prout key1,key2 other shit";//argv[1]
	CommandManager	cmManager;
	size_t			i = 0;
	std::string		cm;

	//create the map with all registered commands
	cmManager.generateCmds();

	//execute command
	i = buffer.find(" ");
	if (i == std::string::npos)
		i = buffer.size() - 1;
	cm.assign(buffer, 0, i);
	buffer.erase(0, i + 1);
	cmManager.executeCm(cmManager.getCmd(cm).process(buffer, client));
}