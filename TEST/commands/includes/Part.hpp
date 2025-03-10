/*

//requirement
registration succeeded

//parsing
at least 1 param
params are seperated with a coma ","
<channel>{,<channel>} [<reason>] (pour qu'il y ait des espaces dans reason il faut que le message commence par des :)

//attributes
command name : PART
command issuer client object
channel object

//methods
-- checkers --
(1) enoughParam() -> checks if there are the right nb of params \
				in case of failure display ERR_NEEDMOREPARAMS

(2) validChan() -> checks if channel exists if not display ERR_NOSUCHCHANNEL

(3) onChan() -> checks if the client belongs to the channel \
			if not display ERR_NOTONCHANNEL 

-- executors --
rmFromChan() -> removes client from channel \
				send a PART message to the client, with the reason (if given) \
				(optionnal?) send a message to the other clients of the channel \
				saying that the client left

*/

/*

PART #tosti bye bye (n'a pas pris le message entier car pas les deux points ":" devant)
:bobyy!~boobyy@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr PART #tosti :bye
#JOIN #tosti key
:lithium.libera.chat 421 bobyy #JOIN :Unknown command
JOIN #tosti key
:bobyy!~boobyy@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr JOIN #tosti
:lithium.libera.chat 332 bobyy #tosti :pizza
:lithium.libera.chat 333 bobyy #tosti bobyy!~boobyy@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr 1741120314
:lithium.libera.chat 353 bobyy @ #tosti :bobyy @chacham
:lithium.libera.chat 366 bobyy #tosti :End of /NAMES list.
PART #tosti :by ebye bye
:bobyy!~boobyy@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr PART #tosti :by ebye bye


*/