# Parsing messages

## Table of content

- [Parsing messages](#parsing-messages)
  - [Table of content](#table-of-content)
    - [IRC messages](#irc-messages)
      - [Validating messages](#validating-messages)
    - [Prefixes / sources](#prefixes--sources)
      - [Validating prefixes / sources](#validating-prefixes--sources)
    - [Commands](#commands)
      - [Validating commands](#validating-commands)
    - [Command parameters](#command-parameters)
      - [Validating parameters](#validating-parameters)
    - [Message separator](#message-separator)
  - [Appendix](#appendix)
    - [IRC PSEUDO-BNF](#irc-pseudo-bnf)
    - [**BNF syntax**](#bnf-syntax)
    - [Sources](#sources)

---

### IRC messages

See [appendix](#bnf-syntax) for how to read the following documentation.

Messages from clients will default to the server unless specifically sent to another client.
The server may send a client a message (IE to confirm that a command has been excecuted, or not.)
They may consist from three parts, separated by a single ASCII space (0x20 or 32)

Messages are formed in the following way:

```markdown
<message>  ::= [':' <prefix> <SPACE> ] <command> <params> <crlf>
```

We will expand on that structure hereafter.

#### Validating messages

- Messages **SHOULD NOT** be longer than 512 characters.
  - If they are, return 417 - ERR_INPUTTOOLONG
- The server **SHOULD** ignore empty messages
- The server **SHOULD** be able to handle single `\n` and `\r` at the end of a message, treating them as if it were a `\r\n` pair.

### Prefixes / sources

The _prefix_ or _source_ of a message is optionnal. It serves as a way to identify the _origin_ of the message and is mostly used in server-to-client connections, where the prefix is the server name.

It can also be used in client-originated messages that are being relayed by the server (ie. private messages, to indicate the sender)

The prefix is structured as follows:

```markdown
<prefix>   ::= <servername> | <nick> [ '!' <user> ] [ '@' <host> ]
```

The clients MUST NOT include a source when sending a messages. In the case of a client-to-client message, the server adds the source to the message it relays in the following format:

```markdown
:<prefix> <SPACE>
for a client    `:nickname!username@hostname`
for the server  `:server-hostname`
```

If the server receives a client message including a prefix, the prefix is ignored and the command is processed without it.

#### Validating prefixes / sources

- **MUST** start with a `':'`
- **MUST** end with a `' '`
- in the case that it's a user prefix:
  - MAY have a `!`
  - MAY have a `@`

### Commands

The _commands_ can be represented as a string ('KICK') or a numeric (004). This is determined by the direction of the message:

- in client-to-server: string;
- In server-to-client: numeric.

The structure is as follows:

```markdown
<command>  ::= <letter> { <letter> } | <number> <number> <number>
```

For commands we **should** implement in ft_irc, see [commands.md](commands.md).

#### Validating commands

- **MUST** be a command that we handle.

### Command parameters

There can be up to 15 command parameters; the server **MUST** fail gracefully if there is more.
The parameters change meaning for each command and **MUST** be interpreted by the individual commands.

There are two kinds of parameters: **middle** and **trailing**.

A **middle** parameter is a string separated by one or more space(s).
It **MUST NOT** contain a SPACE, NULL, CR or LF parameter and it **MUST NOT** start by a `:`.

```markdown
<middle>   ::= <Any *non-empty* sequence of octets not including SPACE
               or NUL or CR or LF, the first of which may not be ':'>

|CMD  | MIDDLE PARAM |
|KICK | amelie38     |
```

A parameter containing a space that is not prefixed by a `:` will be considered as two parameters.

A **trailing parameter** is the parsing fix to that issue. It allows the user to include spaces in their parameters. It **MUST** be placed at the end of the message, because the parsing will consider everything after the `:` to be a single parameter.
Encountering a colon in a message means that the parameter following it will be the last one.

For instance, this:

```markdown
KICK amelie38 :being annoying
```

Will result in amelie38 being kicked for the reason "being annoying", whereas this :

```markdown
KICK :amelie38 being annoying
```

Will fail because the server will interpret the parameter to be "amelie38 being annoying", and will not be able to find a user bearing that nickname.

Once the parsing is done, all parameters are equivalent. The trailing parameter is stripped of its prefixing `:`

#### Validating parameters

Middle parameters:

- **MUST NOT** exceed 15
  - if there are more than 15 parameters, only 15 will be processed.
- **MUST NOT** contains `' '`, `\r`, `\n` or NULL.

Trailing parameters:

- **MUST** start with `:`
- **MUST NOT** contain NULL, `\r`, `\n`
- **MAY** be empty
- **MAY** contain zero or more space(s).

### Message separator

Messages MUST be separated by `\r\n` or `0x0D0x0A`.

## Appendix

### IRC PSEUDO-BNF

```markdown
<prefix>   ::= <servername> | <nick> [ '!' <user> ] [ '@' <host> ]
<command>  ::= <letter> { <letter> } | <number> <number> <number>
<SPACE>    ::= ' ' { ' ' }
<params>   ::= <SPACE> [ ':' <trailing> | <middle> <params> ]
<middle>   ::= <Any *non-empty* sequence of octets not including SPACE
               or NUL or CR or LF, the first of which may not be ':'>
<trailing> ::= <Any, possibly *empty*, sequence of octets not including
                 NUL or CR or LF>
<crlf>     ::= \r\n (CR LF)
```

### [**BNF syntax**][def]

- `|` indicates choice
- `::=` indicates the expression expands to the right hand-side of the expression
- angle brackets (`<text>`) indicates that something should be subsituted.
- square brackets (`[text]`) indicates an optional parameter
- curly braces `{text}` indicates that the parameter can be repeated more than once.

### Sources

- [RFC 1459 IRC Documentation - Section 2.3](https://www.rfc-editor.org/rfc/rfc1459#section-2.3)
- [Modern IRC Documentation - Message Format](https://modern.ircdocs.horse/#message-format)

[def]: https://www.geeksforgeeks.org/bnf-notation-in-compiler-design/
