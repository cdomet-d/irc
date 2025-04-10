//HEADER

#include "CmdExecution.hpp"

bool ping(Client &sender) {
	std::string mess = sender.mess.getMess();

	size_t i = mess.find(" ");
	std::string name = mess.substr(0, i);
	if (name == "PING") {
		mess.erase(0, i);
		reply::send_(sender.getFd(),
					 ":irc.bitchat.net PONG irc.bitchat.net :" + mess);
		return (true);
	}
	return (false);
}
