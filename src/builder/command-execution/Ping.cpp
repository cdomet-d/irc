//HEADER

#include "CmdExecution.hpp"

void ping(CmdSpec &cmd) {
	RPL::send_(cmd.getSdFd(),
				 ":irc.bitchat.net PONG irc.bitchat.net :" + cmd[message_][0]);
}
