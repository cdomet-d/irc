/*

//requirement
registration succeeded

//parsing

//attributes
command name : MODE

//methods
-- checkers --
validChan() -> checks if channel exists if not display ERR_NOSUCHCHANNEL

hasChanPriv() -> checks if client has the appropriate channel privileges to execute command \
					if not display ERR_CHANOPRIVSNEEDED

-- executors --
changeMode() -> sets or removes given mode \
					if <modestring> is not given display RPL_CHANNELMODEIS \
					followed 


*/