#include "Cmd.hpp"
#include "Reply.hpp"

void cmd::join(const int fd, const std::string &target) {
	RPL::send_(fd, "JOIN " + target + "\r\n");
}

// void cmd::answer(const int fd, const std::string &target) {}

void cmd::disconnect(const int fd) {
	RPL::send_(fd, "ft-friend disconnecting! Bye!\r\nQUIT\r\n");
}

static bool isLowercase(const std::string &login) {
	for (std::string::const_iterator it = login.begin(); it != login.end(); ++it) {
		if (!islower(*it))
			return false;
	}
	return true;
}

bool cmd::parseLogin(std::string &login) {
	if ((login.size() > 9 && login.size() < 2) || login.empty())
		return false;
	if (login.at(0) == ':')
		login.erase(login.begin());
	if (login.at(0) != '!')
		return false;
	login.erase(login.begin());
	if (!isLowercase(login))
		return false;
	return true;
}
