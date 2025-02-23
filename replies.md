
| NUM_VAL | TEXT                 | MESSAGE                                                                       |
|---------|----------------------|-------------------------------------------------------------------------------|
| 431     | ERR_NONICKNAMEGIVEN  | ":No nickname given"                                                          |
| 432     | ERR_ERRONEUSNICKNAME | "nick:Erroneous nickname"                                                     |
| 433     | ERR_NICKNAMEINUSE    | "<nick> :Nickname is already in use"                                          |
| 461     | ERR_NEEDMOREPARAMS   | "command: Not enough parameters"                                              |
| 462     | ERR_ALREADYREGISTRED | ":Unauthorized command (already registered)"                                  |
| 436     | ERR_NICKCOLLISION    | "nick :Nickname collision KILL from user@host" (not sure we'll need that one) |
| 437     | ERR_UNAVAILRESOURCE  | "nick/channel :Nick/channel is temporarily unavailable"                       |
| 462     | ERR_ALREADYREGISTRED | ":Unauthorized command (already registered)"                                  |
| 462     | ERR_ALREADYREGISTRED | ":Unauthorized command (already registered)"                                  |
| 462     | ERR_ALREADYREGISTRED | ":Unauthorized command (already registered)"                                  |

# COMMAND PASS
The PASS command is used to set a 'connection password'.  The optional password can and MUST be set 
before any attempt to register the connection is made.  
Currently this requires that user send a PASS command before sending the NICK/USER combination.

           ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED

# COMMAND NICK
NICK command is used to give user a nickname or change the existing one.

           ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
           ERR_NICKNAMEINUSE               ERR_NICKCOLLISION (unlisted: we're not implementing multiple servers)
           ERR_UNAVAILRESOURCE             ERR_RESTRICTED (unlisted: we're not implementing user modes)

# COMMAND USER
The USER command is used at the beginning of connection to specify the username, hostname and realname of a new user.

		ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED