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
(1) enoughParam() -> checks if there are the right nb of params \
				in case of failure display ERR_NEEDMOREPARAMS

(2) validChan() -> checks if channel exists if not display ERR_NOSUCHCHANNEL

(3) onChan() -> checks if the client belongs to the channel \
			if not display ERR_NOTONCHANNEL 

(if channel has invite-only mode, only an operator can invite)
(4) hasChanPriv() -> checks if client has the appropriate channel privileges to execute command \
					if not display ERR_CHANOPRIVSNEEDED

(?) validInvite() -> checks if the target user is already on the channel \
					if so display ERR_USERONCHANNEL

-- executors --
inviteUser() -> add the target user to the channel \
				send a RPL_INVITING to the command issuer \
				send an INVITE message with the issuer as <source> to the target user

*/