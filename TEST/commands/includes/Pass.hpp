/*

//parsing :
there must be only one param <password>
can there be spaces in a password ??
<password>

//attributes
command name : PASS
state : done or not (could be used to know if we can execute the command NICK) //actually not mandatory but if used must be the first ?
command issuer client object

// methods :
-- checkers -- :
(1) enoughParam() -> checks if there are the right nb of params \
				in case of failure display ERR_NEEDMOREPARAMS

(2) ERR_ALREADYREGISTERED

(3) pwMatch() -> checks to see if the given password is correct \
			in case of failure display ERR_PASSWDMISMATCH

-- executors -- :
setPw() -> sets clients password to given string

*/

/*
PASS
:tantalum.libera.chat 461 * PASS :Not enough parameters

PASS
:copper.libera.chat 462 juliette :You are already connected and cannot handshake again
*/