/*

//requirement
registration succeeded

//parsing
at least 1 param, there can be 2 : <channel> [<topic>]
channel object
command issuer client object

//methods
-- checkers --
enoughParam() -> checks if there are the right nb of params \
				in case of failure display ERR_NEEDMOREPARAMS

validChan() -> checks if channel exists if not display ERR_NOSUCHCHANNEL

(if the client wants to view the topic of a channel but is not on it we can prohibit it. it's up to us)
onChan() -> checks if the client belongs to the channel \
			if not display ERR_NOTONCHANNEL

(if MODE +t is set and client wants to change topic)
hasChanPriv() -> checks if client has the appropriate channel privileges to execute command \
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