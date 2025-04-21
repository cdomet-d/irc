#include "Reply.hpp"
#include "Bot.hpp"
#include <cstring>
#include <ctime>
#include <iostream>
#include <sys/socket.h>

static bool doNotLog(const std::string &message) {
	return (message.find("PING") != std::string::npos
			|| message.find("PONG") != std::string::npos
			|| message.find("WHO") != std::string::npos);
}

/* get timestamp*/
static std::string ts() {
	char time_buf[80];
	time_t now = time(0);
	strftime(time_buf, sizeof(time_buf), "%d-%m-%Y %H:%M:%S", localtime(&now));
	return (time_buf);
}

void RPL::send_(int fd, std::string reply) {
	RPL::log(RPL::REPLY, reply);
	size_t bytes = send(fd, reply.c_str(), strlen(reply.c_str()),
						MSG_EOR | MSG_DONTWAIT | MSG_NOSIGNAL);
	if (bytes != strlen(reply.c_str()))
		RPL::log(ERROR, "Not send in full: \t", reply);
}

void RPL::log(e_level level, std::string message) {
	Bot &bot = Bot::getInstance(0, "", "");
	if (doNotLog(message))
		return;
	if (bot.log_.is_open()) {
		switch (level) {
		case INFO:
			bot.log_ << "[" << ts() << "] INFO  " << message << std::flush;
			break;
		case ERROR:
			bot.log_ << "[" << ts() << "] ERROR " << message << std::flush;
			std::cerr << "[" << ts() << "] ERROR " << message << std::flush;
			break;
		case DEBUG:
			bot.log_ << "[" << ts() << "] DEBUG " << message << std::flush;
			break;
		case REPLY:
			bot.log_ << "[" << ts() << "] >> " << message << std::flush;
			break;
		case GOT:
			bot.log_ << "[" << ts() << "] << " << message << std::flush;
			break;
		}
	}
}

void RPL::log(e_level level, std::string message, std::string verbose) {
	Bot &bot = Bot::getInstance(0, "", "");
	if (bot.log_.is_open()) {
		switch (level) {
		case (INFO):
			bot.log_ << "[" << ts() << "] INFO  " << message << verbose
					 << std::flush;
			break;
		case (ERROR):
			bot.log_ << "[" << ts() << "] ERROR " << message << verbose
					 << std::flush;
			break;
		case (DEBUG):
			bot.log_ << "[" << ts() << "] DEBUG " << message << verbose
					 << std::flush;
			break;
		case (REPLY):
			bot.log_ << "[" << ts() << "] >> " << message << verbose
					 << std::flush;
			break;
		case GOT:
			bot.log_ << "[" << ts() << "] << " << message << std::flush;
			break;
		}
	}
}
