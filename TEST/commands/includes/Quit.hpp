/*

//requirements
registration 0

//parsing
one optional argument : [<quit message>]

//attributes
command name : QUIT
command issuer client object

//methods
cutConnexion() -> send ERROR message to client then rm client from struct epoll \
				send message to clients from same channel as the exiting client : \
				if command QUIT was sent by the client \
					<source> (the exiting client) + "Quit: " + <quit message> (if given) \
				else \
					message will explain why this connection broke

*/