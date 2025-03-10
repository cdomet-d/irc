
# COMMAND PASS

The PASS command is used to set a 'connection password'.  The optional password can and MUST be set 
before any attempt to register the connection is made.  
Currently this requires that user send a PASS command before sending the NICK/USER combination.

```text
           ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED
```text

# COMMAND NICK

NICK command is used to give user a nickname or change the existing one.

```text
           ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
           ERR_NICKNAMEINUSE               ERR_NICKCOLLISION (unlisted: we're not implementing multiple servers)
           ERR_UNAVAILRESOURCE             ERR_RESTRICTED (unlisted: we're not implementing user modes)
```

# COMMAND USER

The USER command is used at the beginning of connection to specify the username, hostname and realname of a new user.

```text
        ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED
```

# COMMAND JOIN

```text
           ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN
           ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
           ERR_CHANNELISFULL               ERR_BADCHANMASK
           ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS (what is the maximum amount of channels ?)
           RPL_TOPIC
```

If a JOIN is successful, the user is then sent the channel's topic
(using RPL_TOPIC) and the list of users who are on the channel (using
RPL_NAMREPLY), which must include the user joining.

RPL_NAMREPLY which is mentionned in the doc but not under numeric replies:

```text
        353     RPL_NAMREPLY "<channel> :[[@|+]<nick> [[@|+]<nick> [...]]]" 
```

# COMMAND PRIVMSG

```text
            ERR_NORECIPIENT                 ERR_NOTEXTTOSEND
            ERR_CANNOTSENDTOCHAN            ERR_NOTOPLEVEL
            ERR_WILDTOPLEVEL                ERR_TOOMANYTARGETS
            ERR_NOSUCHNICK
            RPL_AWAY
```

```text
    404     ERR_CANNOTSENDTOCHAN
            "<channel name> :Cannot send to channel"

    - Sent to a user who is either (a) not on a channel
        which is mode +n or (b) not a chanop (or mode +v) on
        a channel which has mode +m set and is trying to send
        a PRIVMSG message to that channel.

    413     ERR_NOTOPLEVEL
                "<mask> :No toplevel domain specified"
    414     ERR_WILDTOPLEVEL
                
                "<mask> :Wildcard in toplevel domain"

        - 412 - 414 are returned by PRIVMSG to indicate that
            the message wasn't delivered for some reason.
            ERR_NOTOPLEVEL and ERR_WILDTOPLEVEL are errors that
            are returned when an invalid use of
            "PRIVMSG $<server>" or "PRIVMSG #<host>" is attempted.
```

# COMMAND KICK

```text
        ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
        ERR_BADCHANMASK                 ERR_CHANOPRIVSNEEDED
        ERR_NOTONCHANNEL
```

# ALL COMMANDS

| NUM_VAL | TEXT                 | MESSAGE                                                         |
|---------|----------------------|-----------------------------------------------------------------|
| 332     | RPL_TOPIC            | "< channel > :< topic >"                                        |
| 403     | ERR_NOSUCHCHANNEL    | "< channel name > :No such channel"                             |
| 431     | ERR_NONICKNAMEGIVEN  | ":No nickname given"                                            |
| 432     | ERR_ERRONEUSNICKNAME | "< nick > :Erroneous nickname"                                  |
| 433     | ERR_NICKNAMEINUSE    | "< nick > :Nickname is already in use"                          |
| 437     | ERR_UNAVAILRESOURCE  | "< nick/channel> : < Nick/channel > is temporarily unavailable" |
| 461     | ERR_NEEDMOREPARAMS   | "< command > : Not enough parameters"                           |
| 462     | ERR_ALREADYREGISTRED | ":You may not reregister"                                       |
| 471     | ERR_CHANNELISFULL    | "< channel > :Cannot join channel (+l)"                         |
| 473     | ERR_INVITEONLYCHAN   | "< channel > :Cannot join channel (+i)"                         |
| 405     | ERR_TOOMANYCHANNELS  | "< channel name > :You have joinehrd too many channels"         |
| 411     | ERR_NORECIPIENT      | ":No recipient given (< command >)"                             |
| 404     | ERR_CANNOTSENDTOCHAN | "< channel name > :Cannot send to channel"                      |
| 401     | ERR_NOSUCHNICK       | "< nickname > :No such nick/channel"                            |
| 301     | RPL_AWAY             | "< nick > :< away message >"                                    |
| 474     | ERR_BANNEDFROMCHAN   | "< channel > :Cannot join channel (+b)"                         |
| 412     | ERR_NOTEXTTOSEND     | ":No text to send"                                              |
| 475     | ERR_BADCHANNELKEY    | "< channel > :Cannot join channel (+k)"                         |
| 475     | ERR_BADCHANNELKEY    | "< channel > :Cannot join channel (+k)"                         |
| 475     | ERR_BADCHANNELKEY    | "< channel > :Cannot join channel (+k)"                         |
| 475     | ERR_BADCHANNELKEY    | "< channel > :Cannot join channel (+k)"                         |
| 475     | ERR_BADCHANNELKEY    | "< channel > :Cannot join channel (+k)"                         |
