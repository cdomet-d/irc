//HEADER

#include "CmdExecution.hpp"

void ping(CmdSpec &cmd) {
	reply::send_(cmd.getSdFd(),
				 ":irc.bitchat.net PONG irc.bitchat.net :" + cmd[message_][0]);
}
