/*

//requirement
registration succeeded

//parsing
just 2 params : <user> <password>

//attributes
command name : OPER
command issuer client object
channel object

//methods
-- checkers --
clientAuth() -> checks if the client has the right to become an operator \
				if not display ERR_NOOPERHOST

pwMatch() -> checks to see if the given password is correct \
			in case of failure display ERR_PASSMISMATCH

enoughParam() -> checks if there are the right nb of params \
				in case of failure display ERR_NEEDMOREPARAMS

-- executors --
setOper() -> changes client status, give client the prefix "@" \
				send concerned client RPL_YOUROPER message \
				and a MODE message indicating his new user modes \
				also inform network of this new operator using MODE +o

*/