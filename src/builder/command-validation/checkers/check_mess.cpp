//HEADER

#include "validator.hpp"

bool check::mess(CmdSpec &cmd, int idx) {
	(void)idx;
	if (!check::mess_::params(cmd))
		return (false);

	size_t i = 0;
	while (i < cmd[target_].size()) {
		if (!check::mess_::prefix(cmd, i) || !check::target(cmd, i)) {
			cmd[target_].rmParam(i);
			continue;
		}
		i++;
	}
	if (!cmd[target_].size())
		return (false);
	return (true);
}

bool check::mess_::params(CmdSpec &cmd) {
	if (cmd[target_].empty()) {
		reply::send_(
			cmd.getSender().getFd(),
			ERR_NORECIPIENT(cmd.getSender().cliInfo.getNick(), cmd.getName()));
		return (false);
	}
	if (cmd[message_].empty()) {
		reply::send_(cmd.getSender().getFd(),
					 ERR_NOTEXTTOSEND(cmd.getSender().cliInfo.getNick()));
		return (false);
	}
	return (true);
}

bool check::mess_::prefix(CmdSpec &cmd, int idx) {
	if (cmd[target_][idx].size() > 1 && cmd[target_][idx][1] == '#') {
		if (cmd[target_][idx][0] != '@') {
			reply::send_(cmd.getSender().getFd(),
						 ERR_BADCHANMASK(cmd[target_][idx]));
			return (false);
		}
		cmd[target_].trimParam(idx, 0, 1);
		cmd.setOnlyOp();
	}
	return (true);
}
