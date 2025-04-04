# Checkers inventory

| Checker                                  | Numeric reply                       | Purpose                                                                                |
|------------------------------------------|-------------------------------------|----------------------------------------------------------------------------------------|
| *missing checker*                        | ERR_INVALIDMODEPARAM                | checks if mode flags' arguments are valid                                              |
| check::**chan**                          | ERR_NOSUCHCHANNEL                   | checks if channel exists                                                               |
| check::**enoughParams**                  | ERR_NEEDMOREPARAMS                  | checks if any mandatory parameter is empty                                             |
| check::**invite**                        | ERR_USERONCHANNEL                   | checks if target isn't already on the channel                                          |
| check::**nick**                          | ERR_NONICKNAMEGIVEN                 | - checks if the param nickname was given<br>- calls **syntaxIsValid** and **isUnique** |
| check::**target**                        | ERR_NOSUCHNICK                      | checks if target exists                                                                |
| check::**targetIsOnChan**                | ERR_USERNOTINCHANNEL                | checks if target is on the channel                                                     |
| check::**user**                          | \                                   | checks USERLEN and silently trims if necessary                                         |
| check::chans_::**hasChanAuthorisations** | ERR_CHANOPRIVSNEEDED                | checks if sender is an operator                                                        |
| check::chans_::**isOnChan**              | ERR_NOTONCHANNEL                    | checks if sender is in the channel                                                     |
| check::join_::**chanHasRoom**            | ERR_CHANNELISFULL                   | if channel has +l, it checks if there is some room left                                |
| check::join_::**cliHasMaxChans**         | ERR_TOOMANYCHANNELS                 | checks if the number of channels the sender is in hasn't reached the limit             |
| check::join_::**hasInvite**              | ERR_INVITEONLYCHAN                  | if channel has +i mode, it checks if sender has an invite                              |
| check::join_::**validKey**               | ERR_BADCHANNELKEY                   | if channel has +k, it checks if the given key is valid                                 |
| check::mess_::**params**                 | ERR_NORECIPIENT<br>ERR_NOTEXTTOSEND | checks if privmsg's params aren't empty                                                |
| check::mode_::**flagIsValid**            | ERR_UNKNOWNMODE                     | checks if mode flag is valid                                                           |
| check::nick_::**isUnique**               | ERR_NICKNAMEINUSE                   | checks if nickname isn't already used                                                  |
| check::nick_::**syntaxIsValid**          | ERR_ERRONEUSNICKNAME                | checks nickname syntaxe                                                                |
| check::register_::**isRegistered**       | ERR_ALREADYREGISTRED                | checks if client isn't already registered                                              |
| check::register_::**pwMatch**            | ERR_PASSWDMISMATCH                  | checks if password is valid                                                            |
| check::register_::**stageDone**          | ERR_NEEDNICK<br>ERR_NEEDUSER        | checks if command was already done during registration                                 |
| CmdSpec::**checkRegistrationStage**      | ERR_NOTREGISTERED                   | checks if client has appropriate registration lvl to execute command                   |

## Extended checkers

**Extended checkers** are all used by commands who have a list of a param. They loop on that list, remove any member of said list that isn't valid and at the end if the list is empty they return false

| Extended checkers | Purpose                                                                                                                                                                                                        |
|-------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| check::**join**   | loops on all channels and calls check::join_::**assessRequest**                                                                                                                                                |
| check::**kick**   | loops on all targets and calls check::target and check::**targetIsOnChan**                                                                                                                                     |
| check::**mess**   | loops on all targets and needs to call check::**target** or  check::**chan** and check::chans_::**isOnChan**<br>-> doesn't work because of privmsg params' enum (this is where check::exists would be usefull) |
| check::**mode**   | loops on all flags and calls check::mode_::**flagIsValid** and *missing checker*                                                                                                                               |
| check::**part**   | loops on all channels and calls check::**chan** and check::chans_::**isOnChan**                                                                                                                                |

## Commands and their associated checkers

| Command | Checkers                                                                                                                                                                                                            |
|---------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| INVITE  | - check::**enoughParams**<br>- check::**target**<br>- check::**chan**<br>- check::chans_::**isOnChan**<br>- check::**invite**<br>- check::chans_::**hasChanAuthorisations**                                         |
| JOIN    | - check::**enoughParams**<br>- check::**join**<br>- check::**findString**<br>- check::join_::**chanHasRoom**<br>- check::join_::**hasInvite**<br>- check::join_::**validKey**<br>- check::join_::**cliHasMaxChans** |
| KICK    | - check::**enoughParams**<br>- check::**chan**<br>- check::chans_::**isOnChan**<br>- check::chans_::**hasChanAuthorisations**<br>-  check::**kick**<br>- check::**target**<br>- check::**targetIsOnChan**           |
| MODE    | - check::**enoughParams**<br>- check::**chan**<br>- check::chans_::**isOnChan**<br>- check::chans_::**hasChanAuthorisations**<br>- check::**mode**<br>- check::mode_::**flagIsValid**<br>- missing checker          |
| NICK    | - check::register_::**stageDone**<br>- check::**nick**<br>- check::nick_::**syntaxIsValid**<br> - check::nick_::**isUnique**                                                                                        |
| PART    | - check::**enoughParams**<br>- check::**part**<br>- check::**chan**<br>- check::chans_::**isOnChan**                                                                                                                |
| PASS    | - check::register_::**stageDone**<br>- check::register_::**isRegistered**<br>- check::**enoughParams**<br>- check::register_::**pwMatch**                                                                           |
| PRIVMSG | - check::**mess**<br>- needs a solution                                                                                                                                                                             |
| QUIT    | \                                                                                                                                                                                                                   |
| TOPIC   | - check::**enoughParams**<br>- check::**chan**<br>- check::chans_::**isOnChan**<br>- check::chans_::**hasChanAuthorisations**                                                                                       |
| USER    | - check::register_::**isRegistered**<br>- check::**enoughParams**<br>- check::**user**                                                                                                                              |
| WHO     | - check::**enoughParams**<br>- check::**chan**<br>- check::chans_::**isOnChan**<br>- check::mode_::**flagIsValid** (doesn't have correct proto)                                                                     |

## Simplifying the checkers

Things we need to check:

- [X] que le channel existe
- [X] que l'utilisateur existe
- [ ] que la syntaxe est correcte, quelque qu'elle soit
- [ ] que l'utilisateur est sur le channel
- [ ] que l'utilisateur a les droits de ce qu'il essaye de faire

And then, command specific things that will be defined later.

But the most repetitive tasks imply checking that things exists and that the syntax is correct.

## Proposal

We should have one checker for each command, each taking a `cmdSpec`. We already have those in `validator.hpp`.

Those specific checkers will be attributed in the command manager, and then proceed to call generic subcheckers.

## Generic checkers

### Similar checkers

- check::**chan**, check::**target** and check::**nick_::isUnique**
- check::chans_::**isOnChan**, check::**targetIsOnChan** and check::**invite**

Create two functions:

```cpp
/* define a template for all the maps */
 template < typename MapType >
 bool exists(std::string arg, const MapType &map) {
  typename MapType::const_iterator toFind = map.find(arg);
  if (toFind == map.end())
   return false;
  return true;
 }
```
