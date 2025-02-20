/*

//parsing :
there must be only one param <password>
can there be spaces in a password ??

// methods :
-- checkers -- :
pwMatch() -> checks to see if the given password is the same as the server's \
			in case of failure display ERR_PASSMISMATCH

enoughParam() -> checks if there are the right nb of params \
				in case of failure display ERR_NEEDMOREPARAMS

-- setters -- :
setPw(std::string param) -> sets clients password to given string \
							if already set display ERR_ALREADYREGISTERED

//attributes
state : done or not (could be used to know if we can execute the command NICK)


*/