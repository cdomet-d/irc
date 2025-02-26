# Parsing rules

Source: [IRC Documentation - Section 2.3](https://www.rfc-editor.org/rfc/rfc1459#section-2.3)

## IRC messages

See [appendix](#bnf-syntax) for how to read the following documentation.

Messages from clients will default to the server unless specifically sent to another client.
The server may send a client a message (IE to confirm that a command has been excecuted, or not.)
They may consist from three parts, separated by a single ASCII space (0x20 or 32)

Messages are formed in the following way:

```markdown
<message>  ::= [':' <prefix> <SPACE> ] <command> <params> <crlf>
```

We will expand on that structure hereafter.

### Prefixes

The _prefix_ of a message is optionnal. It serves as a way to identify the _origin_ of the message and is mostly used in server-to-client connections, where the prefix is the server name. 

It can also be used in client-originated messages that are being relayed by the server (ie. private messages, to indicate the sender)

The structure is as follows:

```markdown
<prefix>   ::= <servername> | <nick> [ '!' <user> ] [ '@' <host> ]
```

In the context of a command, it is defined as

```markdown
:<prefix> <SPACE>
````

Examples:

```markdown
# <prefix>   ::= <servername> 
    :irc-server 
# <prefix>   ::= <nick> [ '!' <user> ] [ '@' <host> ]
    :amelie38!amelie@host.com 

```




- the command;
  - it can be represented as a string ('KICK') or a numeric (004)
    - In client-to-server: string litteral;
    - In server-to-client: a numeric reply.
  - it has the following syntax:
    - `<command>  ::= <letter> { <letter> } | <number> <number> <number>`
- the command parameters (up to 15).
- the message separator, `\r\n` or `0x0D0x0A`

#### IRC rules

```markdown
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