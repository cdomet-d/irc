/*

//requirement
registration succeeded

//parsing
at least 1 param (we can restrict the nbr of channels)
params are seperated with a coma ","

//attributes
command name : JOIN

//methods
-- checkers --
enoughParam() -> checks if there are the right nb of params \
				in case of failure display ERR_NEEDMOREPARAMS

validChan() -> checks if channel exists if not display ERR_NOSUCHCHANNEL 

joinChanRequest() -> checks : 
						- the nbr of channels the client is in, if > limit display ERR_TOOMANYCHANNELS \
						- if the key to access the channel (if it has one) is supplied and valid \
							if not display ERR_BADCHANNELKEY \
						- if client isn't banned from the channel if so display ERR_BANNEDFROMCHAN \
						- if channel's client limit (if set) hasn't been reached if so display ERR_CHANNELISFULL \
						- if client was invited (if channel is invite-only mode) if not display ERR_INVITEONLYCHAN \
						- ERR_BADCHANMASK (not sure of the purpose of this one)
						
-- setters --
addToChan() -> adds client to channel \
				send the 3 following messages in this order : \
					- client as the source and the joined channel as first param \
					- channel's topic (if it has one) \
					- a list of users in that channel \
				send message about all commands which affect channel \
				MODE, KICK, PART, QUIT, PRIVMSG (not sure when to send this message)
				

*/