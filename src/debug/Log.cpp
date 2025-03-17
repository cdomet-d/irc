/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Log.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:56:23 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/12 16:48:06 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <ctime>

std::string timeStamp()
{
	char time_buf[80];
	time_t now = time(0);
	strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
	return (time_buf);
}

void log(logLevel level, std::string message)
{
	switch (level) {
	case INFO:
		std::cout << "[" << timeStamp() << "] INFO:\t" << BLUE << message
				  << RESET << std::endl;
		break;
	case ERROR:
		std::cout << "[" << timeStamp() << "] ERROR:\t" << RED << message
				  << RESET << std::endl;
		break;
	case DEBUG:
		std::cout << "[" << timeStamp() << "] DEBUG:\t" << YELLOW << message
				  << RESET << std::endl;
		break;
	}
}

void log(logLevel level, std::string message, std::string additionalInfo)
{
	switch (level) {
	case (INFO):
		std::cout << "[" << timeStamp() << ']' << " INFO:\t" << BLUE << message
				  << additionalInfo << RESET << std::endl;
		break;
	case (ERROR):
		std::cout << "[" << timeStamp() << ']' << " ERROR:\t" << RED << message
				  << additionalInfo << RESET << std::endl;
		break;
	case (DEBUG):
		std::cout << "[" << timeStamp() << ']' << " DEBUG:\t" << YELLOW
				  << message << additionalInfo << RESET << std::endl;
		break;
	}
}
