/*

//requirement
registration succeeded

//parsing
at least 1 param (we can restrict the nbr of channels)
params are seperated with a coma ","
can accept param "0" which acts like a PART command (do we want to do that ?)
<channel>{,channel} [key{,key}]

//attributes
command name : JOIN
command issuer client object
channel object

//methods
-- checkers --
(1) enoughParam() -> checks if there are the right nb of params \
				in case of failure display ERR_NEEDMOREPARAMS

(2) validChan() -> checks if channel exists if not display ERR_NOSUCHCHANNEL (si pas les bons charactere dans le nom ex : cha sans le #) \
					different pour les autres commandes, qui elles regardent juste si le channel existe alors que pour join il regarde s'il est correcte

(3) joinChanRequest() -> checks : 
						- the nbr of channels the client is in, if > limit display ERR_TOOMANYCHANNELS \
						(1) - if the key to access the channel (if it has one) is supplied and valid \
							if not display ERR_BADCHANNELKEY \
						- if client isn't banned from the channel \
								if so display ERR_BANNEDFROMCHAN (we don't have to implement MODE +b so this is optionnal) \
						- if channel's client limit (if set) hasn't been reached if so display ERR_CHANNELISFULL \
						(2) - if client was invited (if channel is invite-only mode) if not display ERR_INVITEONLYCHAN \
						- ERR_BADCHANMASK (not sure of the purpose of this one) Indicates the supplied channel name is not a valid. \
							 is similar to, but stronger than, ERR_NOSUCHCHANNEL (403), which indicates that the channel does not exist, but that it may be a valid name.
						
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

/*

JOIN
:lithium.libera.chat 461 chacham JOIN :Not enough parameters
JOIN channel
:lithium.libera.chat 403 chacham channel :No such channel
JOIN #channe 
:chacham!~chalortte@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr JOIN #channe
:lithium.libera.chat MODE #channe +Cnst
:lithium.libera.chat 353 chacham @ #channe :@chacham
:lithium.libera.chat 366 chacham #channe :End of /NAMES list.

JOIN #cha,lolo,#hihi
:lithium.libera.chat 403 chacham lolo :No such channel
:chacham!~chalortte@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr JOIN #cha
:lithium.libera.chat MODE #cha +Cnst
:lithium.libera.chat 353 chacham @ #cha :@chacham
:lithium.libera.chat 366 chacham #cha :End of /NAMES list.
:chacham!~chalortte@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr JOIN #hihi
:lithium.libera.chat MODE #hihi +Cnst
:lithium.libera.chat 353 chacham @ #hihi :@chacham
:lithium.libera.chat 366 chacham #hihi :End of /NAMES list.

MODE #hihi +k key
:chacham!~chalortte@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr MODE #hihi +k key
JOIN #hihi 
:platinum.libera.chat 475 bobyy #hihi :Cannot join channel (+k) - bad key
JOIN #hihi,#cha key1,key
:platinum.libera.chat 475 bobyy #hihi :Cannot join channel (+k) - bad key
:bobyy!~cha@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr JOIN #cha
:platinum.libera.chat 353 bobyy @ #cha :bobyy @chacham
:platinum.libera.chat 366 bobyy #cha :End of /NAMES list.
JOIN #hihi key jekfheriuhfr
:bobyy!~cha@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr JOIN #hihi
:platinum.libera.chat 353 bobyy @ #hihi :bobyy @chacham
:platinum.libera.chat 366 bobyy #hihi :End of /NAMES list.


JOIN #chaaaa
:chacham!~chalortte@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr JOIN #chaaaa
:lithium.libera.chat MODE #chaaaa +Cnst
:lithium.libera.chat 353 chacham @ #chaaaa :@chacham
:lithium.libera.chat 366 chacham #chaaaa :End of /NAMES list.
MODE #chaaaa +i
:chacham!~chalortte@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr MODE #chaaaa +i
JOIN #chaaaa
:platinum.libera.chat 473 bobyy #chaaaa :Cannot join channel (+i) - you must be invited
INVITE bobyy #chaaaa
:lithium.libera.chat 341 chacham bobyy #chaaaa
:chacham!~chalortte@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr INVITE bobyy :#chaaaa
JOIN #chaaaa
:bobyy!~cha@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr JOIN #chaaaa
:platinum.libera.chat 353 bobyy @ #chaaaa :bobyy @chacham
:platinum.libera.chat 366 bobyy #chaaaa :End of /NAMES list.

JOIN #loli kekeeke
:lithium.libera.chat 475 chacham #loli :Cannot join channel (+k) - bad key
JOIN #loli key
:lithium.libera.chat 473 chacham #loli :Cannot join channel (+i) - you must be invited
*/