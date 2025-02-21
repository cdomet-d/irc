/*

//requirement
registration succeeded

//parsing
at least 2 params
if more, params are seperated with a coma ","
(we can limit the nbr of target usersper KICK command)

//attributes
command name : KICK

//methods
-- checkers --
enoughParam() -> checks if there are the right nb of params \
				in case of failure display ERR_NEEDMOREPARAMS

validChan() -> checks if channel exists if not display ERR_NOSUCHCHANNEL

onChan() -> checks if the client belongs to the channel \
			if not display ERR_NOTONCHANNEL 

hasChanPriv() -> checks if client has the appropriate channel privileges to execute command \
					if not display ERR_CHANOPRIVSNEEDED

-- executors --
kickUser() -> remove from client from channel \
				send KICK message to channel with <source> being the client who sent the kick, \
				the channel and the comment (if given otherwise a default message)


*/