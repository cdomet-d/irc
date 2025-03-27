/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:37:38 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/27 14:20:08 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Reply.hpp"
#include "Server.hpp"
#include <ctime>
#include <sys/socket.h>

static std::string timeStamp() {
	char time_buf[80];
	time_t now = time(0);
	strftime(time_buf, sizeof(time_buf), "%d-%m-%Y %H:%M:%S", localtime(&now));
	return (time_buf);
}

void reply::sendReply(int fd, std::string reply) {
	reply::log(reply::REPLY, reply);
	size_t bytes = send(fd, reply.c_str(), strlen(reply.c_str()),
						MSG_EOR | MSG_DONTWAIT | MSG_NOSIGNAL);
	if (bytes != strlen(reply.c_str()))
		reply::log(ERROR, "Not send in full: \t", reply);
}

void reply::log(e_level level, std::string message) {
	Server &serv = Server::GetServerInstance(0, "");
	if (serv.logfile.is_open()) {
		switch (level) {
		case INFO:
			serv.logfile << "[" << timeStamp() << "] INFO  " << message;
			break;
		case ERROR:
			serv.logfile << "[" << timeStamp() << "] ERROR " << message;
			break;
		case DEBUG:
			serv.logfile << "[" << timeStamp() << "] DEBUG " << message;
			break;
		case REPLY:
			serv.logfile << "[" << timeStamp() << "] REPLY " << message;
			break;
		}
	}
}

void reply::log(e_level level, std::string message, std::string verbose) {
	Server &serv = Server::GetServerInstance(0, "");
	if (serv.logfile.is_open()) {
		switch (level) {
		case (INFO):
			serv.logfile << "[" << timeStamp() << "] INFO  " << message
						 << verbose;
			break;
		case (ERROR):
			serv.logfile << "[" << timeStamp() << "] ERROR " << message
						 << verbose;
			break;
		case (DEBUG):
			serv.logfile << "[" << timeStamp() << "] DEBUG " << message
						 << verbose;
			break;
		case (REPLY):
			serv.logfile << "[" << timeStamp() << "] REPLY " << message
						 << verbose;
			break;
		}
	}
}
