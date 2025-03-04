/*

//requirement
registration succeeded

//parsing
just 2 params
<nickname> <channel>

//attributes
command name : INVITE
command issuer clientfd
list of all clients to find the target and send him the invite

//methods
-- checkers --
(0) enoughParam() -> checks if there are the right nb of params \
				in case of failure display ERR_NEEDMOREPARAMS

(1) verifier si le target existe sinon ERR_NOSUCHNICK

(2) validChan() -> checks if channel exists if not display ERR_NOSUCHCHANNEL

(3) onChan() -> checks if the client belongs to the channel \
			if not display ERR_NOTONCHANNEL 

(4) validInvite() -> checks if the target user is already on the channel \
					if so display ERR_USERONCHANNEL

(5) hasChanPriv() -> checks if client has the appropriate channel privileges to execute command \
					if not display ERR_CHANOPRIVSNEEDED


-- executors --
inviteUser() -> add the target user to the channel \
				send a RPL_INVITING to the command issuer \
				send an INVITE message with the issuer as <source> to the target user

*/

/*

INVITE #chaaaa bobyy
:lithium.libera.chat 401 chacham #chaaaa :No such nick/channel
INVITE bobyy #chaaaa
:lithium.libera.chat 341 chacham bobyy #chaaaa

INVITE bobyy #loooool
:lithium.libera.chat 403 chacham #loooool :No such channel
JOIN #loli
:bobyy!~cha@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr JOIN #loli
:platinum.libera.chat MODE #loli +Cnst
:platinum.libera.chat 353 bobyy @ #loli :@bobyy
:platinum.libera.chat 366 bobyy #loli :End of /NAMES list.
INVITE bobyy #loli
:lithium.libera.chat 442 chacham #loli :You're not on that channel
JOIN #loli
:chacham!~chalortte@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr JOIN #loli
:lithium.libera.chat 353 chacham @ #loli :chacham @bobyy
:lithium.libera.chat 366 chacham #loli :End of /NAMES list.
INVITE chacham #loli
:platinum.libera.chat 443 bobyy chacham #loli :is already on channel

INVITE meee #loli (loli n'est pas en mode +i)
:lithium.libera.chat 482 chacham #loli :You're not a channel operator

INVITE plouk #loli
:lithium.libera.chat 401 chacham plouk :No such nick/channel


*/