# Classes
## Server
- Needs to handle all the client sockets through epoll
  - Needs the epoll structures
- _has-a_ client map listing all client instances 
- _has-a_ channel map listing all channels instances 
- singleton pattern class

## Clients
- Contains all the parameters related to the user 
  - channels they belong to ? 
  - authorisations for channels they're allowed to write in ?
  - nick/pass/etc...?
  - [...]

## Channel
- Contains all the parameters related to the channels 


## Parser
- methods to parse received messages, validate their integrity, eventually reaggregate them ?
  - features need to be better defined to really be developped here.