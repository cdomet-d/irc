/*

//requirements
registration succeeded

//parsing
at least 2 params
if more seperated with ","
<receiver>{,<receiver>} <text to be sent>

//attributes
command name : PRIVMSG
list of all clients to find the target and send him the message
list of all channels to find the target and send it the message
command issuer client object

//methods
-- checkers --
validMess() -> check : \
				- if there is a text to be sent, if not display ERR_NOTEXTTOSEND \
				- if there is a target, if not display ERR_NORECIPIENT
				if target is a channel : \
					- check channel modes because they can affect the message \
							if it cannot be delivered to channel display ERR_CANNOTSENDTOCHAN \
			    else if target is a user : \
					- check if nickname exists, if not display ERR_NOSUCHNICK \


-- executors --
sendMess() -> send <text to be sent> to target \
				if target is a channel, check for a prefixe and \
				send message only to clients with appropriate status \
				else if it is a user, if user has been set as away display RPL_AWAY \ (don't need to do it, it's MODE -a)
				if the target starts with a $, the message is a broadcast (sent to all clients on server)

*/