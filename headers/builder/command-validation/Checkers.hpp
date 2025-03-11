//HEADER

#ifndef CHECKERS_HPP
# define CHECKERS_HPP

# include "CommandSpec.hpp"

class CommandSpec;

int	pwMatch(CommandSpec& cmd);
int	isRegistered(CommandSpec& cmd);
int	validNick(CommandSpec& cmd);
int	validUser(CommandSpec& cmd);
int	validChan(CommandSpec& cmd);
int	joinChanRequest(CommandSpec& cmd);
int	validTarget(CommandSpec& cmd);
int	validInvite(CommandSpec& cmd);
int	onChan(CommandSpec& cmd);
int	hasChanPriv(CommandSpec& cmd);
int	validKick(CommandSpec& cmd);
int	validMode(CommandSpec& cmd);
int	validMess(CommandSpec& cmd);

#endif