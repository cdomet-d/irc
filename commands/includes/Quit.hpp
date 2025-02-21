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
				if command QUIT was sent by the client \
					<source> (the exiting client) + "Quit: " + <quit message> (if given) \
				else \
					message will explain why this connection broke

*/