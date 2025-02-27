/*

//requirement
password is set

//parsing
only one param
<nickname>

//attributes
command name : NICK
state : done or not
command issuer client object
channel object

//methods
-- checkers --
validNick() -> checks if nickname characters are valid or not \
				if no nickname is given display ERR_NONICKNAMEGIVEN \
				if invalid characters display ERR_ERRONEUSNICKNAME \
				if nickname is already in use display ERR_NICKNAMEINUSE

-- executors --
setNick() -> sets client nickname to given string \
				send "<old nickname> [ ["!" user] "@"host ]" message \
				to the concerned client	and if in a channel send to all the channel's clients


*/