# Table of content

- [Table of content](#table-of-content)
	- [Classes](#classes)
		- [Server](#server)
		- [Clients](#clients)
		- [Channel](#channel)
		- [Parser / builder](#parser--builder)
			- [IRC messages](#irc-messages)
			- [IRC rules](#irc-rules)
	- [Appendix:](#appendix)
		- [**BNF syntax**](#bnf-syntax)

## Classes

### Server

- Needs to handle all the client sockets through epoll
  - Needs the epoll structures
- _has-a_ client map listing all client instances
- _has-a_ channel map listing all channels instances
- singleton pattern class

### Clients

- Contains all the parameters related to the user

  - channels they belong to
  - authorisations for channels they're allowed to write in
  - nick/pass/etc...
  - [...]

### Channel

see [channel-types](https://modern.ircdocs.horse/#channel-types)

- Contains all the parameters related to the channels

### Parser / builder

- Features aiming to validate received messages & assess their validity as commands.

Source: [IRC Documentation - Section 2.3](https://www.rfc-editor.org/rfc/rfc1459#section-2.3)

#### IRC messages

See [appendix](#bnf-syntax) for how to read the following documentation.

Messages from clients will default to the server unless specifically sent to another client.
The server may send a client a message (IE to confirm that a command has been excecuted, or not.)
They may consist from three parts, separated by a single ASCII space (0x20 or 32)

- the _prefix_, which is optionnal;
  - it serves as a way to identify the _origin_ of the message.
  - mostly used in server-to-client connections, where the prefix is the server name
  - can also be used in client-originated messages that are being relayed by the server (ie. private messages, to indicate the sender)
  - it has the following syntax:
    - `<prefix>   ::= <servername> | <nick> [ '!' <user> ] [ '@' <host> ]`
  - in the context of a command, it is defined by a `:<prefix> <SPACE>`.
- the command;
  - a command is a way to trigger an action in an IRC server. It is transmitted in a message to the server.
  - it can be represented as a string ('KICK') or a numeric (3 digits, but which ?)
  - it has the following syntax:
    - `<command>  ::= <letter> { <letter> } | <number> <number> <number>`
- the command parameters (up to 15).
- the message separator, `\r\n` or `0x0D0x0A`

#### IRC rules


```markdown
<message>  ::= [':' <prefix> <SPACE> ] <command> <params> <crlf>
<prefix>   ::= <servername> | <nick> [ '!' <user> ] [ '@' <host> ]
<command>  ::= <letter> { <letter> } | <number> <number> <number>
<SPACE>    ::= ' ' { ' ' }
<params>   ::= <SPACE> [ ':' <trailing> | <middle> <params> ]
<middle>   ::= <Any *non-empty* sequence of octets not including SPACE
               or NUL or CR or LF, the first of which may not be ':'>
<trailing> ::= <Any, possibly *empty*, sequence of octets not including
                 NUL or CR or LF>
<crlf>     ::= CR LF
```

## Appendix:

### [**BNF syntax**][def]

- `|` indicates choice
- `::=` indicates the expression expands to the right hand-side of the expression
- angle brackets (`<text>`) indicates that something should be subsituted.
- square brackets (`[text]`) indicates an optional parameter
- curly braces `{text}` indicates that the parameter can be repeated more than once.

[def]: https://www.geeksforgeeks.org/bnf-notation-in-compiler-design/