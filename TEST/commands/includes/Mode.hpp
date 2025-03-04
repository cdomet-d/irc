/*

//requirement
registration succeeded

//parsing
<channel> [<modestring> [<mode arguments>...]]
-+o : give/take channel operator privilege. ex : MODE #channel +o nickname
-+i : set/remove invite-only channel. ex : MODE #channel +i
-+k : set/remove the channel key. ex : MODE #channel +k key
-+t : set/remove the restrictions of the TOPIC command to channel operators. ex : MODE #channel +t
-+l : set/remove the user limit to channel. ex : MODE #channel +l 2 (met une limite a 2 client), MODE #channel -l

//attributes
command name : MODE
channel object
command issuer client object

//methods
-- checkers --
(1) validChan() -> checks if channel exists if not display ERR_NOSUCHCHANNEL

(2) hasChanPriv() -> checks if client has the appropriate channel privileges to execute command \
					if not display ERR_CHANOPRIVSNEEDED

() verifier que chaque mode a bien les arguments qu'il lui faut
pour -+o verifier que le target existe, qu'il soit sur le channel
pour -+i s'il ce mode a deja ete activer et que le client refait un +i, ne rien faire
pour -+k si aucune key n'est donné ne rien faire que ce soit pour le set ou remove car pour remove il faut donner la clé qui a ete set
pour -+t si l'operator est le seul dans le channel et qu'il fait +t, ne rien faire ? (a verifier)


-- executors --
changeMode() -> sets or removes given mode \
					if <modestring> is not given display RPL_CHANNELMODEIS \
					followed 


*/