/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Log.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:56:23 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/18 16:02:42 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Log.h"
#include "Server.hpp"
#include <ctime>
#include <fstream>

std::string timeStamp() {
	char time_buf[80];
	time_t now = time(0);
	strftime(time_buf, sizeof(time_buf), "%d-%m-%Y %H:%M:%S", localtime(&now));
	return (time_buf);
}

void logger(logLevel level, std::string message) {
	std::ofstream logfile("rawlog.log", std::ios::out | std::ios::app);

	if (logfile.is_open()) {
		switch (level) {
		case INFO:
			logfile << "[" << timeStamp() << "] INFO " << message;
			break;
		case ERROR:
			logfile << "[" << timeStamp() << "] ERROR " << message;
			break;
		case DEBUG:
			logfile << "[" << timeStamp() << "] DEBUG " << message;
			break;
		}
	}
	logfile.close();
}

void logger(logLevel level, std::string message, std::string additionalInfo) {

	std::ofstream logfile("rawlog.log", std::ios::out | std::ios::app);

	if (logfile.is_open()) {
		switch (level) {
		case (INFO):
			logfile << "[" << timeStamp() << "] INFO " << message
					<< additionalInfo;
			break;
		case (ERROR):
			logfile << "[" << timeStamp() << "] ERROR " << message
					<< additionalInfo;
			break;
		case (DEBUG):
			logfile << "[" << timeStamp() << "] DEBUG " << message
					<< additionalInfo;
			break;
		}
	}
	logfile.close();
}
