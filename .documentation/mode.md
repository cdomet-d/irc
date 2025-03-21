# Mode

Used to set or remove options from a target (user or channel, though ft-irc's case, just a channel).

The syntax for this command is:

```text
  Parameters: <target> [<modestring> [<mode arguments>...]]
```

- `<target>` is the channel the modes will be applied to.
- `<modestring>` is the flags that will be applied. They can either be set with `+` or removed with `-`. The flags we are implementing are:
  - i: Set/remove Invite-only channel
  - t: Set/remove the restrictions of the TOPIC command to channel operators
  - k: Set/remove the channel key (password)
  - o: Give/take channel operator privilege
  - l: Set/remove the user limit to channel
- `<mode arguments>` is the arguments for the modes. They are _sequentially obtained_ from the string.

[source](https://modern.ircdocs.horse/)

There are four categories of channel modes, defined as follows:

- **Type A**: Modes that add or remove an address to or from a list. These modes MUST always have a parameter when sent from the server to a client. A client MAY issue this type of mode without an argument to obtain the current contents of the list. The numerics used to retrieve contents of Type A modes depends on the specific mode. Also see the EXTBAN parameter.
- **Type B**: Modes that change a setting on a channel. These modes MUST always have a parameter.
- **Type C**: Modes that change a setting on a channel. These modes MUST have a parameter when being set, and MUST NOT have a parameter when being unset.
- **Type D**: Modes that change a setting on a channel. These modes MUST NOT have a parameter.

For type A, B, and C modes, arguments will be sequentially obtained from `<mode arguments>`. If a type B or C mode does not have a parameter when being set, the server MUST ignore that mode. If a type A mode has been sent without an argument, the contents of the list MUST be sent to the user, unless it contains sensitive information the user is not allowed to access. When the server is done processing the modes, a MODE command is sent to all members of the channel containing the mode changes. Servers MAY choose to hide sensitive information when sending the mode changes.

## CHANMODES Parameter

```text
Format: CHANMODES=A,B,C,D[,X,Y...]
```

The CHANMODES parameter specifies the channel modes available and which types of arguments they do or do not take when using them with the MODE command.

The value lists the channel mode letters of Type A, B, C, and D, respectively, delimited by a comma (',', 0x2C). The channel mode types are defined in the the MODE message description.

To allow for future extensions, a server MAY send additional types, delimited by a comma (',', 0x2C). However, server authors SHOULD NOT extend this parameter without good reason, and SHOULD CONSIDER whether their mode would work as one of the existing types instead. The behaviour of any additional types is undefined.

Server MUST NOT list modes in this parameter that are also advertised in the PREFIX parameter. However, modes within the PREFIX parameter may be treated as type B modes.