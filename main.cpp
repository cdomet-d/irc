/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:11:56 by aljulien          #+#    #+#             */
/*   Updated: 2025/02/18 11:18:05 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arpa/inet.h>
#include <csignal>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <poll.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <vector>

bool sign = false; //global for signal listening

void SIgnalHandler(int signum)
{
	(void)signum;
	sign = true;
}

void AcceptClient(int servSocketFd, std::vector< struct pollfd > fds)
{
	int					Fd;			//client file descriptor
	struct sockaddr_in	clientAdress;		
	struct pollfd 		NewPoll;
	socklen_t 			len = sizeof(clientAdress);

	// accept the new client
	//The accept() function shall extract the first connection on the queue
	// of pending connections, create a new socket with the same socket
	//type protocol and address family as the specified socket, and
	//allocate a new file descriptor for that socket.
	//The function takes a sockaddr struct where the address of the connecting
	//sockets are returned.  
	int incomingFd = accept(servSocketFd, (sockaddr *)&(clientAdress), &len);
	if (incomingFd == -1)
		return;

	// set the socket option (O_NONBLOCK) for non-blocking socket
	if (fcntl(incomingFd, F_SETFL, O_NONBLOCK) == -1)
		return;

	NewPoll.fd = incomingFd;	 // add the client socket to the pollfd
	NewPoll.events = POLLIN;	 // set the event to POLLIN for reading data
	NewPoll.revents = 0;	 	// set the revents to 0

	Fd = incomingFd; // set the client file descriptor
	
	// add the client socket to the pollfd
	fds.push_back(NewPoll);

	std::cout << "Client <" << incomingFd << "> Connected" << std::endl;
}

int servInit()
{
	std::vector< struct pollfd > fds; //vector for fds
	int port = 4444;				  //port of th server
	int servSocketFd;				  //fds of the server
	struct sockaddr_in address;
	struct pollfd newPoll;

	//int representing the address family (IPv4 or IPv6)
	address.sin_family = AF_INET;
	
	//16-bit int representing port number stored as big-endian. Function htons used for conversions
	address.sin_port = htons(port);
	
	//struct in_addr containing the IPv4 address. 
	//The single member of the struct represents 
	//the IPv4 address in network byte order.
	//The INADDR_ANY means any IP address, meaning 
	//the socket will be bound to all available network interfaces on the host
	address.sin_addr.s_addr = INADDR_ANY;

	//We create a socket using the socket function
	//First parameter : int domains, specifies the communication domain. AF_INET is for IPv4 communication
	//Second parameter : int type, specifies the type of communication semantics for the socket. SOCK_STREAM is for TCP sockets
	//Third parameter : int protocol, speficies the protocol to be used with the socket, usually set to 0.
	servSocketFd = socket(AF_INET, SOCK_STREAM, 0);

	
	//setsockopt is used to set options on sockets to control the behavior of the socket
	//First paramter : the fd of the socket
	//Second parameter : int level, indicate the protocol level at which the optiens resides. SOL_SOCKET indicat the options should only be applied to the current socket
	//Thrird parameter : int optname, SO_REUSEADDR option allow for the immediate reuse of local addresses and ports
	//Fourth parameter : pointer to the value that needs to be set for the option
	//Fifth parameter : size of the option value in bytes. Seting the value at 1 means the value is enabled 
	int en = 1;
	if (setsockopt(servSocketFd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) ==
		-1)
		return (0);
	
	//Function is used to perform control operations on fds. Here it's used to set O_NONBLOCK flag on the server socket fd
	if (fcntl(servSocketFd, F_SETFL) == -1)
		return (0);
	
	//Function bind enables you to assign a specific address and port to a socket, providing it with a unique identity in the network
	//Here it's being bind to a IP address but it can also be bind to a hostname
	if (bind(servSocketFd, (struct sockaddr *)&address, sizeof(address)) == -1)
		return (0);
	
	//Function listen set the socket as a passive (server-side connection) socket ready to accept incoming connections.
	//SOMAXCONN refers to the max lenght of the queue of pending connections
	if (listen(servSocketFd, SOMAXCONN) == -1)
		return (0);

	//we initiliaze the newPoll to the server socket
	//It's needed because we will check the socket of the server for new connection
	// and the clients sockets for incoming data. 
	// Adding the server socket to the loop of the poll() function is necessary to detect new connections.
	newPoll.fd = servSocketFd;
	newPoll.events = POLLIN;
	newPoll.revents = 0;
	fds.push_back(newPoll);

	std::cout << "Server listening on port " << port << std::endl;
	while (sign == false) {
		if ((poll(&fds[0], fds.size(), -1) == -1) && sign == false)
			return 0;
		for (size_t i = 0; i < fds.size(); i++) //check all fds
		{
			//revents is filled by the kernel afetr poll returns
			//here we are checking if revents was set at POLLIN, in 
			//which case data is ready to be read on a file descroptor 
			if (fds[i].revents & POLLIN)
			{
				if (fds[i].fd == servSocketFd)
					AcceptClient(servSocketFd, fds); //accept client
			}
		}
	}
	return (0);
}

int main()
{
	signal(SIGINT, SIgnalHandler);
	signal(SIGQUIT, SIgnalHandler);
	servInit();
	return (0);
}