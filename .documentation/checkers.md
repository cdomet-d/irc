| Checker | Numeric reply | Purpose |
| ------- | ------------- | ------- |
| CmdSpec::**checkRegistrationStage** | ERR_NOTREGISTERED | checks if client has appropriate registration lvl to execute command |
| check::**register_::stageDone** | ERR_NEEDNICK<br>ERR_NEEDUSER | checks if command was already done during registration |
| check::**register_::isRegistered** | ERR_ALREADYREGISTRED | checks if client isn't already registered |
| check::**register_::pwMatch** | ERR_PASSWDMISMATCH | checks if password is valid |
| check::**enoughParams** | ERR_NEEDMOREPARAMS | checks if any mandatory parameter is empty |
| check::**nick** | ERR_NONICKNAMEGIVEN | checks if the param nickname was given |
| check::**nick_::syntaxIsValid** | ERR_ERRONEUSNICKNAME | checks nickname syntaxe |
| check::**nick_::isUnique** | ERR_NICKNAMEINUSE | checks if nickname isn't already used |
| check::**user** | | checks USERLEN and silently trims if necessary |
| check::**join_::hasInvite** | ERR_INVITEONLYCHAN | if channel has +i mode, it checks if sender has an invite |
| check::**join_::validKey** | ERR_BADCHANNELKEY | if channel has +k, it checks if the given key is valid |
| check::**join_::chanHasRoom** | ERR_CHANNELISFULL | if channel has +l, if checks if there is some room left |
| check::**join_::cliHasMaxChans** | ERR_TOOMANYCHANNELS | checks if the number of channels the sender is in hasn't reached the limit |
| check::**chan** | ERR_NOSUCHCHANNEL | checks if channel exists |
| check::chans_::**isOnChan** | ERR_NOTONCHANNEL | checks if sender is in the channel |
| check::chans_::**hasChanAuthorisations** | ERR_CHANOPRIVSNEEDED | checks if sender is an operator |
| check::**target** | ERR_NOSUCHNICK | checks if target exists |
| check::**targetIsOnChan** | ERR_USERNOTINCHANNEL | checks if target isn't already on the channel|
| check::**mode_::flagIsValid** | ERR_UNKNOWNMODE | checks if mode flag is valid |
| *missing checker* | ERR_INVALIDMODEPARAM | checks if mode flags' arguments are valid |
| check::**mess_::params** | ERR_NORECIPIENT<br>ERR_NOTEXTTOSEND | checks if privmsg's params aren't empty |

<br><br>

| Command | Checkers |
| ------- | -------- |
| PASS | - check::register_::**stageDone**<br>- check::register_::**isRegistered**<br>- check::**enoughParams**<br>- check::register_::**pwMatch** |
| NICK | - check::register_::**stageDone**<br>- check::**nick**<br> ` - check::nick_::syntaxIsValid`<br>  ` - check::nick_::isUnique` |



<br><br><br><br>