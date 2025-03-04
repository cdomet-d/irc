/*

//requirement
registration succeeded

//parsing
at least 1 param, there can be 2 : <channel> [<topic>]
channel object
command issuer client object

//methods
-- checkers --
(1) enoughParam() -> checks if there are the right nb of params \
				in case of failure display ERR_NEEDMOREPARAMS

(2) validChan() -> checks if channel exists if not display ERR_NOSUCHCHANNEL

(if the client wants to view the topic of a channel but is not on it we can prohibit it. it's up to us)
(3) onChan() -> checks if the client belongs to the channel \
			if not display ERR_NOTONCHANNEL

(if MODE +t is set and client wants to change topic)
(4) hasChanPriv() -> checks if client has the appropriate channel privileges to execute command \
					if not display ERR_CHANOPRIVSNEEDED

-- executors --
changeTopic() -> if topic (can be NULL) is given change the channel's topic \
					use displayTopic() to send message to each client in the channel \
					including the author of the change. \
					if the topic is changed to exacly the same as it was \
					we can choose to notify the users or not

displayTopic() -> display RPL_TOPIC followed by RPL_TOPICWHOTIME \
					or RPL_NOTOPIC if channel lacks a topic

*/

/*

TOPIC
:lithium.libera.chat 461 chacham TOPIC :Not enough parameters
TOPIC tosti
:lithium.libera.chat 403 chacham tosti :No such channel
TOPIC #lizerhleikj
:lithium.libera.chat 403 chacham #lizerhleikj :No such channel

TOPIC #tosti
:lithium.libera.chat 442 bobyy #tosti :You're not on that channel

TOPIC #tosti 
:lithium.libera.chat 331 bobyy #tosti :No topic is set.
TOPIC #tosti pizza
:lithium.libera.chat 482 bobyy #tosti :You're not a channel operator
:chacham!~char@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr MODE #tosti -t 
TOPIC #tosti pizza
:bobyy!~boobyy@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr TOPIC #tosti :pizza
TOPIC #tosti
:lithium.libera.chat 332 bobyy #tosti :pizza
:lithium.libera.chat 333 bobyy #tosti bobyy!~boobyy@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr 1741120314

*/