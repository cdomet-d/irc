/*

//requirement
registration succeeded

//parsing
<channel> [<modestring> [<mode arguments>...]]

//attributes
command name : MODE
channel object
command issuer client object

//methods
-- checkers --
(1) validChan() -> checks if channel exists if not display ERR_NOSUCHCHANNEL

(2) hasChanPriv() -> checks if client has the appropriate channel privileges to execute command \
					if not display ERR_CHANOPRIVSNEEDED

//other

-- executors --
changeMode() -> sets or removes given mode \
					if <modestring> is not given display RPL_CHANNELMODEIS \
					followed 


*/