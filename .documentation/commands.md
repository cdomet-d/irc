# Commands structure, parsing rules and examples

- [Commands structure, parsing rules and examples](#commands-structure-parsing-rules-and-examples)
	- [PASS](#pass)
		- [Parsing rules](#parsing-rules)
			- [Failure strategy](#failure-strategy)
			- [Success strategy](#success-strategy)
	- [NICK](#nick)
		- [Parsing rules](#parsing-rules-1)
			- [Failure strategy](#failure-strategy-1)
			- [Success strategy](#success-strategy-1)
	- [USER](#user)

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

- Informs the clients that the client changed his NICK, using the old nick as a source.

## NICK

```markdown
NICK : <nickname>
  -> ex : /nick my_nickname
```

### Parsing rules

- MUST NOT contain any of the following characters:
  - space (`' '`, 0x20),
  - comma (`','`, 0x2C),
  - asterisk (`'*'`, 0x2A),
  - question mark (`'?'`, 0x3F),
  - exclamation mark (`'!'`, 0x21),
  - at sign (`'@'`, 0x40)
- MUST NOT start with any of the following characters:
  - dollar (`'$'`, 0x24),
  - colon (`':'`, 0x3A),
  - hash (`'#'`, 0x23 ),
  - ampersand (`'&'`, 0x26)
  - Those result in => ERR_ERRONEUSNICKNAME
- SHOULD NOT contain any dot character (`'.'`, 0x2E)
- MUST NOT already be in use => ERR_NICKNAMEINUSE
- SHOULD NOT be ambiguous with implemented commands.

#### Failure strategy

- Returns the appropriate numeric reply to the client
- Ignore the command

#### Success strategy

- Informs the clients that the client changed his NICK, using the old nick as a source.

```markdown
    NICK amelie
    REPLY: amelie38 changed their nickname to amelie
```

## USER

```markdown
USER : <username> 0 * <realname>
  -> ex : /user my_username 0 * :My real name
```

```markdown
OPER : <user> <password>
  -> ex : /oper my_username my_password
```

```markdown
QUIT : [<quit message>]
  -> ex : /quit going to eat. bye !
```

```markdown
JOIN : <channel>{,channel} [key{,key}]
  -> ex : /join #channel_name
```

```markdown
PART : <channel>{,<channel>} [<reason>]
  -> ex : /part #channel_name Got to go
```

```markdown
TOPIC : <channel> [<topic>]
  -> ex : /topic #channel_name Pizza
```

```markdown
INVITE : <nickname> <channel>
  -> ex : /invite some_nickname #channel_name
```

```markdown
KICK : <channel> <user> *("," <user> ) [<comment>]
  -> ex : /kick #Z1 CronchCronch Badly behaved
```

```markdown
PRIVMSG : <receiver>{,<receiver>} <text to be sent>
  -> ex : /msg username_or_channel Hey how are you ?
```

```markdown
MODE : <channel> [<modestring> [<mode arguments>...]]
  -> ex : /mode #channel_name [+|-]modes params```
