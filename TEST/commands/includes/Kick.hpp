/*

//requirement
registration succeeded

//parsing
at least 2 params
if more, params are seperated with a coma ","
(we can limit the nbr of target users per KICK command)
<channel> <user> *("," <user> ) [<comment>]

//attributes
command name : KICK
command issuer client object
channel object

//methods
-- checkers --
(1) enoughParam() -> checks if there are the right nb of params \
				in case of failure display ERR_NEEDMOREPARAMS

(2) validChan() -> checks if channel exists if not display ERR_NOSUCHCHANNEL

(3) onChan() -> checks if the client belongs to the channel \
			if not display ERR_NOTONCHANNEL 

(4) hasChanPriv() -> checks if client has the appropriate channel privileges to execute command \
					if not display ERR_CHANOPRIVSNEEDED

(?) validKick() -> checks if target user is in the channel \
				if not display ERR_USERNOTINCHANNEL

-- executors --
kickUser() -> remove target user from channel \
				send KICK message to channel with <source> being the client who sent the kick, \
				the channel and the comment (if given otherwise a default message)

*/

/*

KICK #loli urghghri
:lithium.libera.chat 442 chacham #loli :You're not on that channel

KICK #loli hudhekjfb
:lithium.libera.chat 482 chacham #loli :You're not a channel operator

KICK #loli ufhzrubz
:platinum.libera.chat 401 bobyy ufhzrubz :No such nick/channel

KICK #loli zeufhzoir,chacham
:platinum.libera.chat 401 bobyy zeufhzoir :No such nick/channel
KICK #loli chacham,oziefheif
:bobyy!~cha@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr KICK #loli chacham :chacham

KICK
:lithium.libera.chat 461 chacham KICK :Not enough parameters
KICK loli
:lithium.libera.chat 461 chacham KICK :Not enough parameters
KICK loli bobyy
:lithium.libera.chat 403 chacham loli :No such channel
KICK loli ueirfhozrieh
:lithium.libera.chat 403 chacham loli :No such channel
KICK #loli zoiefheoz
:lithium.libera.chat 442 chacham #loli :You're not on that channel
JOIN #loli key
:chacham!~chalortte@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr JOIN #loli
:lithium.libera.chat 353 chacham @ #loli :chacham @bobyy
:lithium.libera.chat 366 chacham #loli :End of /NAMES list.
KICK #loli zefuherb
:lithium.libera.chat 482 chacham #loli :You're not a channel operator
KICK #loli rferere
:platinum.libera.chat 401 bobyy rferere :No such nick/channel
KICK #loli chacham
:bobyy!~cha@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr KICK #loli chacham :chacham
KICK #loli chacham
:platinum.libera.chat 441 bobyy chacham #loli :They aren't on that channel

*/