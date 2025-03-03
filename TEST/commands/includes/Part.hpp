/*

//requirement
registration succeeded

//parsing
at least 1 param
params are seperated with a coma ","
<channel>{,<channel>} [<reason>] 

//attributes
command name : PART
command issuer client object
channel object

//methods
-- checkers --
enoughParam() -> checks if there are the right nb of params \
				in case of failure display ERR_NEEDMOREPARAMS

validChan() -> checks if channel exists if not display ERR_NOSUCHCHANNEL

onChan() -> checks if the client belongs to the channel \
			if not display ERR_NOTONCHANNEL 

-- executors --
rmFromChan() -> removes client from channel \
				send a PART message to the client, with the reason (if given) \
				(optionnal) send a message to the other clients of the channel \
				saying that the client left

*/