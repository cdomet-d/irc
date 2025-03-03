/*

//requirement
registration succeeded

//parsing
at least 2 params
if more, params are seperated with a coma ","
(we can limit the nbr of target users per KICK command)
<channel> <user> *("," <user> ) [<comment>]

//attributes
command name : KICK
command issuer client object
channel object

//methods
-- checkers --
(1) enoughParam() -> checks if there are the right nb of params \
				in case of failure display ERR_NEEDMOREPARAMS

(2) validChan() -> checks if channel exists if not display ERR_NOSUCHCHANNEL

(3) onChan() -> checks if the client belongs to the channel \
			if not display ERR_NOTONCHANNEL 

(4) hasChanPriv() -> checks if client has the appropriate channel privileges to execute command \
					if not display ERR_CHANOPRIVSNEEDED

(?) validKick() -> checks if target user is in the channel \
				if not display ERR_USERNOTINCHANNEL

-- executors --
kickUser() -> remove target user from channel \
				send KICK message to channel with <source> being the client who sent the kick, \
				the channel and the comment (if given otherwise a default message)

*/