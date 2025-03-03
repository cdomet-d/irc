/*

//requirements
- nickname is set
- registration not complete, if so display ERR_ALREADYREGISTERED

//parsing
2 or 4 arguments (to be decided)
<username> 0 * <realname> 

//attributes
command name : NICK
state : done or not
command issuer client object

//Methods
-- checkers --
validUser() -> checks if param characters are valid or not \
				and if username has the right length (will be truncated if not)

enoughParam() -> checks if there are the right nb of params \
				in case of failure display ERR_NEEDMOREPARAMS

-- executors --
setUser() -> sets client's username, realname, (hostname, servername) \

*/