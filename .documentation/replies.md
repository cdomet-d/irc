
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
        353     RPL_NAMREPLY "< channel > :[[@|+]< nick > [[@|+]< nick > [...]]]" 
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
            "< channel name > :Cannot send to channel"|

    - Sent to a user who is either (a) not on a channel
        which is mode +n or (b) not a chanop (or mode +v) on
        a channel which has mode +m set and is trying to send
        a PRIVMSG message to that channel.

    413     ERR_NOTOPLEVEL
                "< mask > :No toplevel domain specified"|
    414     ERR_WILDTOPLEVEL
                
                "< mask > :Wildcard in toplevel domain"|

        - 412 - 414 are returned by PRIVMSG to indicate that
            the message wasn't delivered for some reason.
            ERR_NOTOPLEVEL and ERR_WILDTOPLEVEL are errors that
            are returned when an invalid use of
            "PRIVMSG $< server >" or "PRIVMSG #< host >" is attempted.
```

# COMMAND KICK

```text
        ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
        ERR_BADCHANMASK                 ERR_CHANOPRIVSNEEDED
        ERR_NOTONCHANNEL
```

# ALL COMMANDS

| NUM_VAL | TEXT                 | MESSAGE                                                                                   |
|---------|----------------------|-------------------------------------------------------------------------------------------|
| 001     | RPL_WELCOME          | "Welcome to the Internet Relay Network < nick >!< user >@< host >"                        |
| 002     | RPL_YOURHOST         | "Your host is < servername >, running version < ver >"                                    |
| 003     | RPL_CREATED          | "This server was created < date >"                                                        |
| 004     | RPL_MYINFO           | "< servername > < version > < available user modes > < available channel modes >"         |
| 301     | RPL_AWAY             | "< nick > :< away message >"                                                              |
| 324     | RPL_CHANNELMODEIS    | "< channel > < mode > < mode params >"                                                    |
| 331     | RPL_NOTOPIC          | "< channel > :No topic is set"                                                            |
| 332     | RPL_TOPIC            | "< channel > :< topic >"                                                                  |
| 341     | RPL_INVITING         | "< channel > < nick >"                                                                    |
| 353     | RPL_NAMREPLY         | "( "=" / "*" / "@" ) < channel > :[ "@" / "+" ] < nick > *( " " [ "@" / "+" ] < nick > )" |
| 366     | RPL_ENDOFNAMES       | "< channel > :End of /NAMES list"                                                         |
| 401     | ERR_NOSUCHNICK       | "< nickname > :No such nick/channel"                                                      |
| 403     | ERR_NOSUCHCHANNEL    | "< channel name > :No such channel"                                                       |
| 404     | ERR_CANNOTSENDTOCHAN | "< channel name > :Cannot send to channel"                                                |
| 405     | ERR_TOOMANYCHANNELS  | "< channel name > :You have joined too many channels"                                     |
| 407     | ERR_TOOMANYTARGETS   | "< target > :Too many targets"                                                            |
| 411     | ERR_NORECIPIENT      | ":No recipient given (< command >)"                                                       |
| 411     | ERR_NORECIPIENT      | ":No recipient given (< command >)"                                                       |
| 412     | ERR_NOTEXTTOSEND     | ":No text to send"                                                                        |
| 412     | ERR_NOTEXTTOSEND     | ":No text to send"                                                                        |
| 417     | ERR_INPUTTOOLONG     | ":Input line was too long"                                                                |
| 421     | ERR_UNKNOWNCOMMAND   | "< command > :Unknown command"                                                            |
| 431     | ERR_NONICKNAMEGIVEN  | ":No nickname given"                                                                      |
| 432     | ERR_ERRONEUSNICKNAME | "< nick > :Erroneous nickname"                                                            |
| 433     | ERR_NICKNAMEINUSE    | "< nick > :Nickname is already in use"                                                    |
| 441     | ERR_USERNOTINCHANNEL | "< nick > < channel > :They aren't on that channel"                                       |
| 442     | ERR_NOTONCHANNEL     | "< channel > :You're not on that channel"                                                 |
| 443     | ERR_USERONCHANNEL    | "< user > < channel > :is already on channel"                                             |
| 461     | ERR_NEEDMOREPARAMS   | "< command > :Not enough parameters"                                                      |
| 462     | ERR_ALREADYREGISTRED | ":You may not reregister"                                                                 |
| 471     | ERR_CHANNELISFULL    | "< channel > :Cannot join channel (+l)"                                                   |
| 472     | ERR_UNKNOWNMODE      | "< char > :is unknown mode char to me"                                                    |
| 473     | ERR_INVITEONLYCHAN   | "< channel > :Cannot join channel (+i)"                                                   |
| 474     | ERR_BANNEDFROMCHAN   | "< channel > :Cannot join channel (+b)"                                                   |
| 475     | ERR_BADCHANNELKEY    | "< channel > :Cannot join channel (+k)"                                                   |
| 482     | ERR_CHANOPRIVSNEEDED | "< channel > :You're not channel operator"                                                |
