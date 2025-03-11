//HEADER

#ifndef CHECKERS_HPP
# define CHECKERS_HPP

# include "CmdSpec.hpp"

class CmdSpec;

int	pwMatch(CmdSpec& cmd);
int	isRegistered(CmdSpec& cmd);
int	validNick(CmdSpec& cmd);
int	validUser(CmdSpec& cmd);
int	validChan(CmdSpec& cmd);
int	joinChanRequest(CmdSpec& cmd);
int	validTarget(CmdSpec& cmd);
int	validInvite(CmdSpec& cmd);
int	onChan(CmdSpec& cmd);
int	hasChanPriv(CmdSpec& cmd);
int	validKick(CmdSpec& cmd);
int	validMode(CmdSpec& cmd);
int	validMess(CmdSpec& cmd);

#endif