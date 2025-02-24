/*

//requirement
registration succeeded

//parsing
at least 1 param (we can restrict the nbr of channels)
params are seperated with a coma ","
can accept param "0" which acts like a PART command (do we want to do that ?)

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
						- if client isn't banned from the channel \
								if so display ERR_BANNEDFROMCHAN (we don't have to implement MODE +b so this is optionnal) \
						- if channel's client limit (if set) hasn't been reached if so display ERR_CHANNELISFULL \
						- if client was invited (if channel is invite-only mode) if not display ERR_INVITEONLYCHAN \
						- ERR_BADCHANMASK (not sure of the purpose of this one)
						
-- executors --
addToChan() -> adds client to channel \
				- send the 3 following messages to the client in this order : \
					- client as the source and the joined channel as first param \
					- channel's topic (if it has one) with RPL_TOPIC\
					- a list of users in that channel with RPL_NAMREPLY and RPL_ENDOFNAMES \
							(seems to be the job of the command NAME so not sure we'll do it) \
				- send to client message about all commands which affect channel \
					MODE, KICK, PART, QUIT, PRIVMSG (not sure when to send this message)
				- send a JOIN message to channel to inform other clients
				

*/