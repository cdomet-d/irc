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
				(1) - if there is a text to be sent, if not display ERR_NOTEXTTOSEND \
				(2) - if there is a target, if not display ERR_NORECIPIENT
(3)
if target is a channel : \
	- check channel modes because they can affect the message \ (we don't have modes that can affect a message)
			if it cannot be delivered to channel display ERR_CANNOTSENDTOCHAN \
else if target is a user : \
	- validTarget() -> check if nickname exists, if not display ERR_NOSUCHNICK \

-- executors --
sendMess() -> send <text to be sent> to target \
				if target is a channel, check for a prefixe and send message only to clients with appropriate status \
				else if it is a user, if user has been set as away display RPL_AWAY \ (don't need to do it, it's MODE -a)
				if the target starts with a $, the message is a broadcast (sent to all clients on server)
				if there is a @ in front of the channel name, send message only to operators on that channel (not mandatory)
					ex : PRIVMSG @#tosti hey
				(tips : on saura que c'est un channel grace au #)

*/