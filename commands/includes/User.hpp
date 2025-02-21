/*

//requirement
nickname is set

//parsing
2 or 4 arguments (to be decided)

//attributes
command name : NICK
state : done or not

//Methods
-- checkers --
validUser() -> checks if param characters are valid or not \
				and if username has the right length (will be truncated if not)

enoughParam() -> checks if there are the right nb of params \
				in case of failure display ERR_NEEDMOREPARAMS

-- executors --
setUser() -> sets client's username, realname, (hostname, servername) \
				if already set display ERR_ALREADYREGISTERED

*/