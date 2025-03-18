# Command specifications analysis

- [Command specifications analysis](#command-specifications-analysis)
  - [PASS](#pass)
    - [Parsing rules](#parsing-rules)
      - [Failure strategy](#failure-strategy)
      - [Success strategy](#success-strategy)
    - [Attributes](#attributes)
    - [Methods](#methods)
    - [Tests with libera.chat](#tests-with-liberachat)
  - [NICK](#nick)
  - [tests with libera.chat :](#tests-with-liberachat-)
  - [USER](#user)
  - [tests with libera.chat :](#tests-with-liberachat--1)
  - [INVITE](#invite)
  - [tests with libera.chat :](#tests-with-liberachat--2)
  - [JOIN](#join)
  - [tests with libera.chat :](#tests-with-liberachat--3)
  - [KICK](#kick)
  - [tests with libera.chat :](#tests-with-liberachat--4)
  - [MODE](#mode)
  - [tests with libera.chat :](#tests-with-liberachat--5)
  - [PART](#part)
  - [tests with libera.chat :](#tests-with-liberachat--6)
  - [PRIVMSG](#privmsg)
  - [QUIT](#quit)
  - [TOPIC](#topic)
  - [tests with libera.chat :](#tests-with-liberachat--7)

## PASS

```markdown
PASS : <password>
  -> ex : /pass my_password
```

### Parsing rules

- MUST be used before sending NICK
- MAY be used several times before sending NICK, but only the last pass will be registered
- MUST have a parameter => 461 - ERR_NEEDMOREPARAM
- Once set, CAN'T be modified => 462 - ERR_ALREADYREGISTERED

#### Failure strategy

- Returns the appropriate numeric reply to the client
- Ignore the command
- If the password doesn't match the registered one, the server SHOULD return 464 - ERR_PASSWDMISMATCH and close the connection with the client.

#### Success strategy

- Informs the clients that the client changed his NICK, using the old nick as a source

### Attributes

- command name : `PASS`
- state : done or not (could be used to know if we can execute the command NICK)

### Methods

```cpp
-- checkers -- :
(1) enoughParam() -> checks if there are the right nb of params \
    in case of failure display ERR_NEEDMOREPARAMS

(2) isRegistered -> check if the password is already set    
    in case of failure display ERR_ALREADYREGISTERED

(3) pwMatch() -> checks to see if the given password is correct \
    in case of failure display ERR_PASSWDMISMATCH

-- executors -- :
setPw() -> sets clients password to given string
```

### Tests with libera.chat

```text
PASS
:tantalum.libera.chat 461 * PASS :Not enough parameters

PASS
:copper.libera.chat 462 juliette :You are already connected and cannot handshake again
```

## NICK

//requirement
password is set

//parsing
only one param
<nickname>

//attributes
command name : NICK
state : done or not
client object
channel object

//methods
-- checkers --
validNick() -> checks if nickname characters are valid or not \
                (1) if no nickname is given display ERR_NONICKNAMEGIVEN \
                (2) if invalid characters display ERR_ERRONEUSNICKNAME \
                (3)	if nickname is already in use display ERR_NICKNAMEINUSE

-- executors --
setNick() -> sets client nickname to given string \
                send "<old nickname> [ ["!" user] "@"host ]" message \
                to the concerned client	and if in a channel send to all the channel's clients

## tests with libera.chat :
NICK
:erbium.libera.chat 431 chacham :No nickname given
NICK 0cha
:erbium.libera.chat 432 chacham 0cha :Erroneous Nickname
NICK chacha
:erbium.libera.chat 433 chacham chacha :Nickname is already in use.
NICK chacham
:chacha!~perle@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr NICK :chacham
NICK chacham
//se passe rien

NICK gg
:lol!~rrrrrrrrr@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr NICK :gg
:NickServ!NickServ@services.libera.chat NOTICE gg :This nickname is registered. Please choose a different nickname, or identify via /msg NickServ IDENTIFY gurki <password>
//
👉 Le pseudo gg est enregistré auprès de NickServ (le service d'enregistrement des pseudos).
🔹 Si c'est ton pseudo → Tu dois t'identifier avec /msg NickServ IDENTIFY <password>.
🔹 Si ce n'est pas ton pseudo → Tu dois choisir un autre pseudo avec /nick NouveauPseudo.

NICK i
:silver.libera.chat 433 gg i :Nickname is already in use.
//
👉 Le pseudo i est déjà utilisé par quelqu'un d'autre, en ce moment même.
🔹 Ce pseudo peut être enregistré ou non, mais il est déjà pris.
🔹 Tu ne peux pas l'utiliser tant que l'autre utilisateur ne se déconnecte pas.


## USER
//requirements
- nickname is set
- registration not complete, if so display ERR_ALREADYREGISTERED

//parsing
4 arguments
<username> 0 * <realname> 

//attributes
command name : NICK
state : done or not
client object

//Methods
-- checkers --
(1) enoughParam() -> checks if there are the right nb of params \
                in case of failure display ERR_NEEDMOREPARAMS

(2) ERR_ALREADYREGISTERED

(3) validUser() -> checks if param characters are valid or not \
                and if username has the right length (will be truncated if not)

-- executors --
setUser() -> sets client's username, realname, (hostname, servername) \

## tests with libera.chat :
USER
:mercury.libera.chat 461 hihi USER :Not enough parameters
USER #yo 0 jaj lo
:mercury.libera.chat NOTICE hihi :*** Your username is invalid. Please make sure that your username contains only alphanumeric characters.
ERROR :Closing Link: lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr (Invalid username [~#yo])

USER rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr 0 * etoile de mer
NICK moijesuis
:nickname!~rrrrrrrrr@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr NICK :moijesuis //username has been truncated !!!!


## INVITE
//requirement
registration succeeded

//parsing
just 2 params
<nickname> <channel>

//attributes
command name : INVITE
command issuer clientfd
list of all clients to find the target and send him the invite

//methods
-- checkers --
(1) enoughParam() -> checks if there are the right nb of params \
                in case of failure display ERR_NEEDMOREPARAMS

(2) validTarget() -> verifier si le target existe sinon ERR_NOSUCHNICK

(3) validChan() -> checks if channel exists if not display ERR_NOSUCHCHANNEL

(4) onChan() -> checks if the client belongs to the channel \
            if not display ERR_NOTONCHANNEL 

(5) validInvite() -> checks if the target user is already on the channel \
                    if so display ERR_USERONCHANNEL

(6) hasChanPriv() -> checks if client has the appropriate channel privileges to execute command \
                    if not display ERR_CHANOPRIVSNEEDED


-- executors --
inviteUser() -> add the target user to the channel \
                send a RPL_INVITING to the command issuer \
                send an INVITE message with the issuer as <source> to the target user

## tests with libera.chat :
INVITE #chaaaa bobyy
:lithium.libera.chat 401 chacham #chaaaa :No such nick/channel
INVITE bobyy #chaaaa
:lithium.libera.chat 341 chacham bobyy #chaaaa

INVITE bobyy #loooool
:lithium.libera.chat 403 chacham #loooool :No such channel
JOIN #loli
:bobyy!~cha@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr JOIN #loli
:platinum.libera.chat MODE #loli +Cnst
:platinum.libera.chat 353 bobyy @ #loli :@bobyy
:platinum.libera.chat 366 bobyy #loli :End of /NAMES list.
INVITE bobyy #loli
:lithium.libera.chat 442 chacham #loli :You're not on that channel
JOIN #loli
:chacham!~chalortte@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr JOIN #loli
:lithium.libera.chat 353 chacham @ #loli :chacham @bobyy
:lithium.libera.chat 366 chacham #loli :End of /NAMES list.
INVITE chacham #loli
:platinum.libera.chat 443 bobyy chacham #loli :is already on channel

INVITE meee #loli (loli n'est pas en mode +i)
:lithium.libera.chat 482 chacham #loli :You're not a channel operator

INVITE plouk #loli
:lithium.libera.chat 401 chacham plouk :No such nick/channel


## JOIN
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
                        (2) - if channel's client limit (if set) hasn't been reached if so display ERR_CHANNELISFULL \
                        (3) - if client was invited (if channel is invite-only mode) if not display ERR_INVITEONLYCHAN \
                            - ERR_BADCHANMASK (not sure of the purpose of this one) Indicates the supplied channel name is not a valid. \
                                 is similar to, but stronger than, ERR_NOSUCHCHANNEL (403), which indicates that the channel does not exist, but that it may be a valid name.
                            - if client is already on channel
                        
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
                
## tests with libera.chat :
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


## KICK
//requirement
registration succeeded

//parsing
at least 2 params
if more, params are seperated with a coma ","
(we can limit the nbr of target users per KICK command)
<channel> <user> *("," <user> ) [<comment>]

//attributes
command name : KICK
command issuer client object
channel object

//methods
-- checkers --
(1) enoughParam() -> checks if there are the right nb of params \
                in case of failure display ERR_NEEDMOREPARAMS

(2) validChan() -> checks if channel exists if not display ERR_NOSUCHCHANNEL

(3) onChan() -> checks if the client belongs to the channel \
            if not display ERR_NOTONCHANNEL 

(4) hasChanPriv() -> checks if client has the appropriate channel privileges to execute command \
                    if not display ERR_CHANOPRIVSNEEDED

(5) validTarget() -> verifier si le target existe sinon ERR_NOSUCHNICK

(6) validKick() -> checks if target user is in the channel \
                if not display ERR_USERNOTINCHANNEL


-- executors --
kickUser() -> remove target user from channel \
                send KICK message to channel with <source> being the client who sent the kick, \
                the channel and the comment (if given otherwise a default message)

## tests with libera.chat :
KICK #loli urghghri
:lithium.libera.chat 442 chacham #loli :You're not on that channel

KICK #loli hudhekjfb
:lithium.libera.chat 482 chacham #loli :You're not a channel operator

KICK #loli ufhzrubz
:platinum.libera.chat 401 bobyy ufhzrubz :No such nick/channel

KICK #loli zeufhzoir,chacham
:platinum.libera.chat 401 bobyy zeufhzoir :No such nick/channel (s'arrete au premier mauvais user)
KICK #loli chacham,oziefheif
:bobyy!~cha@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr KICK #loli chacham :chacham

KICK
:lithium.libera.chat 461 chacham KICK :Not enough parameters
KICK loli
:lithium.libera.chat 461 chacham KICK :Not enough parameters
KICK loli bobyy
:lithium.libera.chat 403 chacham loli :No such channel
KICK loli ueirfhozrieh
:lithium.libera.chat 403 chacham loli :No such channel
KICK #loli zoiefheoz
:lithium.libera.chat 442 chacham #loli :You're not on that channel
JOIN #loli key
:chacham!~chalortte@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr JOIN #loli
:lithium.libera.chat 353 chacham @ #loli :chacham @bobyy
:lithium.libera.chat 366 chacham #loli :End of /NAMES list.
KICK #loli zefuherb
:lithium.libera.chat 482 chacham #loli :You're not a channel operator
KICK #loli rferere
:platinum.libera.chat 401 bobyy rferere :No such nick/channel
KICK #loli chacham
:bobyy!~cha@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr KICK #loli chacham :chacham
KICK #loli chacham
:platinum.libera.chat 441 bobyy chacham #loli :They aren't on that channel


## MODE
//requirement
registration succeeded

//parsing
<channel> [<modestring> [<mode arguments>...]]
-+o : give/take channel operator privilege. ex : MODE #channel +o nickname
-+i : set/remove invite-only channel. ex : MODE #channel +i
-+k : set/remove the channel key. ex : MODE #channel +k key
-+t : set/remove the restrictions of the TOPIC command to channel operators. ex : MODE #channel +t
-+l : set/remove the user limit to channel. ex : MODE #channel +l 2 (met une limite a 2 client), MODE #channel -l

//attributes
command name : MODE
channel object
command issuer client object

//methods
-- checkers --
(1) enoughParam() -> checks if there are the right nb of params \
                in case of failure display ERR_NEEDMOREPARAMS

(2) validChan() -> checks if channel exists if not display ERR_NOSUCHCHANNEL

(3) hasChanPriv() -> checks if client has the appropriate channel privileges to execute command \
                    if not display ERR_CHANOPRIVSNEEDED

(4) validMode() -> verifier que le mode existe sinon ERR_UNKNOWNMODE

(5) verifier que chaque mode a bien les arguments qu'il lui faut sinon ERR_INVALIDMODEPARAM
pour -+o verifier que le target existe et qu'il soit sur le channel
pour -+i si ce mode a deja ete active et que le client refait un +i, ne rien faire
pour -+k si aucune key n'est donné ne rien faire que ce soit pour le set ou remove car pour remove il faut donner la clé qui a ete set
pour -+t 
pour -+l si on met pas le nombre limite ERR_NEEDMOREPARAMS. la limite doit au mois etre 1 

-- executors --
changeMode() -> sets or removes given mode \
                    if <modestring> is not given display RPL_CHANNELMODEIS \
                    followed by RPL_CREATIONTIME

## tests with libera.chat :
MODE #tosti +k key +i
:chacham!~char@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr MODE #tosti +k key // +i n'a pas fonctionné
MODE #tosti +i-k key
:chacham!~char@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr MODE #tosti +i-k *


## PART
//requirement
registration succeeded

//parsing
at least 1 param
params are seperated with a coma ","
<channel>{,<channel>} [<reason>] (pour qu'il y ait des espaces dans reason il faut que le message commence par des :)

//attributes
command name : PART
command issuer client object
channel object

//methods
-- checkers --
(1) enoughParam() -> checks if there are the right nb of params \
                in case of failure display ERR_NEEDMOREPARAMS

(2) validChan() -> checks if channel exists if not display ERR_NOSUCHCHANNEL

(3) onChan() -> checks if the client belongs to the channel \
            if not display ERR_NOTONCHANNEL 

-- executors --
rmFromChan() -> removes client from channel \
                send a PART message to the client, with the reason (if given) \
                (optionnal?) send a message to the other clients of the channel \
                saying that the client left

## tests with libera.chat :
PART #tosti bye bye (n'a pas pris le message entier car pas les deux points ":" devant)
:bobyy!~boobyy@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr PART #tosti :bye
#JOIN #tosti key
:lithium.libera.chat 421 bobyy #JOIN :Unknown command
JOIN #tosti key
:bobyy!~boobyy@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr JOIN #tosti
:lithium.libera.chat 332 bobyy #tosti :pizza
:lithium.libera.chat 333 bobyy #tosti bobyy!~boobyy@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr 1741120314
:lithium.libera.chat 353 bobyy @ #tosti :bobyy @chacham
:lithium.libera.chat 366 bobyy #tosti :End of /NAMES list.
PART #tosti :by ebye bye
:bobyy!~boobyy@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr PART #tosti :by ebye bye


## PRIVMSG
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
                (3) - validTarget() -> check if nickname exists, if not display     ERR_NOSUCHNICK \

if target is a channel : \
    - check channel modes because they can affect the message \ (we don't have modes that can affect a message)
            if it cannot be delivered to channel display ERR_CANNOTSENDTOCHAN \


-- executors --
sendMess() -> send <text to be sent> to target \
                if target is a channel, check for a prefixe and send message only to clients with appropriate status \
                else if it is a user, if user has been set as away display RPL_AWAY \ (don't need to do it, it's MODE -a)
                if the target starts with a $, the message is a broadcast (sent to all clients on server)
                if there is a @ in front of the channel name, send message only to operators on that channel (not mandatory)
                    ex : PRIVMSG @#tosti hey
                (tips : on saura que c'est un channel grace au #)


## QUIT
//requirements
registration 0

//parsing
one optional argument : [<quit message>]

//attributes
command name : QUIT
command issuer client object

//methods
cutConnexion() -> send ERROR message to client then rm client from struct epoll \
                send message to clients from same channel as the exiting client : \
                if command QUIT was sent by the client \
                    <source> (the exiting client) + "Quit: " + <quit message> (if given) \
                else \
                    message will explain why this connection broke


## TOPIC
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

## tests with libera.chat :
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
