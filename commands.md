# Commands structure and examples

```markdown
PASS : <password>
  -> ex : /pass my_password
```

---

## Nickname

```markdown
NICK : <nickname>
  -> ex : /nick my_nickname
```

Parsing rules:

- They MUST NOT contain any of the following characters: space (' ', 0x20), comma (',', 0x2C), asterisk ('*', 0x2A), question mark ('?', 0x3F), exclamation mark ('!', 0x21), at sign ('@', 0x40).
- They MUST NOT start with any of the following characters: dollar ('$', 0x24), colon (':', 0x3A), hash ('#', 0x23 ), ampersand ('&', 0x26)
- They SHOULD NOT contain any dot character ('.', 0x2E)
- They SHOULD NOT be ambiguous with implemented commands.

---

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
  -> ex : /kick #channel_name some_username Badly behaved
```

```markdown
PRIVMSG : <receiver>{,<receiver>} <text to be sent>
  -> ex : /msg username_or_channel Hey how are you ?
```

```markdown
MODE : <channel> [<modestring> [<mode arguments>...]]
  -> ex : /mode #channel_name [+|-]modes params```
