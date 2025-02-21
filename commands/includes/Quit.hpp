/*

//requirements
registration succeeded

//parsing
one optional argument : [<quit message>] can it have spaces ??

//attributes
command name : QUIT

//methods
cutConnexion() -> send ERROR message to client then rm client from struct epoll \
				send message to clients from same channel as the exiting client : \
				if command QUIT is sent by a client \
					<source> (the exiting client) + "Quit: " + <quit message> (if given) \
				else \
					send message explaining why this connection broke

*/