# Main features
## Server
- Needs to handle all the client sockets through epoll
  - Needs the epoll structures
- _has-a_ client ? (see: [class relationships](https://www.bestprog.net/en/2020/03/06/c-types-of-relations-between-classes-is-a-has-a-uses-examples-inheritance-basic-concepts/))

## Clients
- Contains all the parameters related to the user 
  - channels they belong to ? 
  - authorisations for channels they're allowed to write in ?
  - nick/pass/etc...?
  - [...]

	- _has-a_ parser ? 
## Parser
- methods to parse received messages, validate their integrity, eventually reaggregate them ?
  - features need to be better defined to really be developped here.