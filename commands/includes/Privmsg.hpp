/*

//requirements
registration succeeded

//parsing
at least 2 params
if more seperated with ","

//attributes
command name : PRIVMSG

//methods
-- checkers --
validMess() -> if target is a channel check channel modes cause it can affect the message \
				if it cannot be delivered to channel display ERR_CANNOTSENDTOCHAN

-- executors --
sendMess() -> send <text to be sent> to target \
				if target is a channel, check for a prefixe and \
				send message only to clients with appropriate status \
				else if it is a user, if user has been set as away display RPL_AWAY \ (not sure if we have to do this)
				if the target starts with a $, the message is a broadcast

*/