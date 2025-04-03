//HEADER

#include "printers.hpp"
#include "validator.hpp"

bool check::part(CmdSpec &cmd, int idx) {
	(void)idx;
	size_t i = 0;

	while (i < cmd[channel_].size()) {
		if (!check::exists(cmd[channel_][i], cmd.server_.getAllChan()) ||
			!check::chans_::isOnChan(cmd, i)) {
			cmd[channel_].rmParam(i);
			continue;
		}
		i++;
	}
	print::cmdParam(cmd[channel_].getInnerParam(), "part");
	if (cmd[channel_].empty())
		return (false);
	return (true);
}

bool check::kick(CmdSpec &cmd, int idx) {
	(void)idx;
	size_t i = 0;

	while (i < cmd[target_].size()) {
		if (!check::target(cmd, i) || !check::targetIsOnChan(cmd, i)) {
			cmd[target_].rmParam(i);
			continue;
		}
		i++;
	}
	if (cmd[target_].empty())
		return (false);
	return (true);
}
