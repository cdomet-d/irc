/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:37:38 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/24 19:22:46 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Reply.hpp"
#include "Server.hpp"
#include <ctime>
#include <sys/socket.h>

static bool doNotLog(const std::string &message) {
	return (message.find("PING") != std::string::npos ||
			message.find("PONG") != std::string::npos ||
			message.find("WHO") != std::string::npos);
}

static std::string timeStamp() {
	char time_buf[80];
	time_t now = time(0);
	std::strftime(time_buf, sizeof(time_buf), "%d-%m-%Y %H:%M:%S",
				  std::localtime(&now));
	return (time_buf);
}

void RPL::send_(int fd, std::string reply) {
	RPL::log(RPL::REPLY, reply);
	size_t bytes = send(fd, reply.c_str(), reply.size(),
						MSG_EOR | MSG_DONTWAIT | MSG_NOSIGNAL);
	if (bytes != reply.size())
		RPL::log(ERROR, "Not send in full: \t", reply);
}

void RPL::sendMessageChannel(clientMap allCliChannel,
							 const std::string &message) {
	for (clientMapIt it = allCliChannel.begin(); it != allCliChannel.end();
		 ++it)
		RPL::send_(it->second->getFd(), message);
}

void RPL::log(e_level level, std::string message) {
	Server &serv = Server::GetServerInstance(0, "");
	if (doNotLog(message))
		return;
	if (serv.logfile.is_open()) {
		switch (level) {
		case INFO:
			serv.logfile << "[" << timeStamp() << "] INFO  " << message
						 << std::flush;
			break;
		case ERROR:
			serv.logfile << "[" << timeStamp() << "] ERROR " << message
						 << std::flush;
			break;
		case DEBUG:
			serv.logfile << "[" << timeStamp() << "] DEBUG " << message
						 << std::flush;
			break;
		case REPLY:
			serv.logfile << "[" << timeStamp() << "] >> " << message
						 << std::flush;
			break;
		case GOT:
			serv.logfile << "[" << timeStamp() << "] << " << message
						 << std::flush;
			break;
		}
	}
}

void RPL::log(e_level level, std::string message, std::string verbose) {
	Server &serv = Server::GetServerInstance(0, "");
	if (serv.logfile.is_open()) {
		switch (level) {
		case (INFO):
			serv.logfile << "[" << timeStamp() << "] INFO  " << message
						 << verbose << std::flush;
			break;
		case (ERROR):
			serv.logfile << "[" << timeStamp() << "] ERROR " << message
						 << verbose << std::flush;
			break;
		case (DEBUG):
			serv.logfile << "[" << timeStamp() << "] DEBUG " << message
						 << verbose << std::flush;
			break;
		case (REPLY):
			serv.logfile << "[" << timeStamp() << "] >> " << message << verbose
						 << std::flush;
			break;
		case GOT:
			serv.logfile << "[" << timeStamp() << "] << " << message
						 << std::flush;
			break;
		}
	}
}