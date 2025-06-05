# The IRC bot

- [The IRC bot](#the-irc-bot)
	- [Purpose](#purpose)
	- [Key features](#key-features)
	- [Additionnal features (that we can develop if we have more time)](#additionnal-features-that-we-can-develop-if-we-have-more-time)
	- [Alternative approach](#alternative-approach)
	- [Message formatting](#message-formatting)
	- [Expected behavior](#expected-behavior)

## Purpose

The bot allows clients to send logins to a channel, requesting to know where that person is logged in the cluster via an intra API pull.

## Key features

- The bot is a executable that will be compiled and launched separately from the server.
- The bot executable will take the server port and passwords as arguments
- It will connect like a client, then request the creation of the channel #42friends
  - The fact that *this* channel starts with a number will ensure no clients can create his channel and keep him from being locked out of his own channel.
- Clients can then JOIN #42friends to send messages to [request logins](#message-formatting).
- The bot can also be PRIVMSG with a request.

## Additionnal features (that we can develop if we have more time)

- the bot can be invited to other channels
- if a message first char triggers a [login request](#message-formatting), the message is forwarded to the bot that will treat it.
- this adds complexity since it implies to call the bot in PRIVMSG if the [format](#message-formatting) triggers.

## Alternative approach

- Alternatively, we can implement a `BOT` command that will call the bot with the argument passed
  - We will need to add it to the command manager and create new checkers (isBotCommand);
- It might also cause issue of where the bot is allowed to write:
  - does it listen to all channels by defaults ?
  - does he need to be invited first ?

## Message formatting

- The bot will expect one argument
- The argument will have at most 9 lowercase alphabetical characters: the eight letters of the login prefixed with a `!`. See pseudo-BNF below

```text
 bot command := !<letter> {<letter>}
```

## Expected behavior

- If the argument is validated, the bot will trim the `!` and run an API request with the provided argument.
- If the API requests fails, the login doesn't exist and ERR_NOSUCHSTUDENT() is returned,
- Otherwise, the bot sends the place where the student is logged back to the sender of the message (either the PRIVMSG client or the channel if it was sent to a channel).
