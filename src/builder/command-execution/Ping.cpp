//HEADER

#include "CmdExecution.hpp"

void ping(CmdSpec &cmd) {
	reply::send_(cmd.getSdFd(), RPL_PONG(cmd[message_][0]));
}
