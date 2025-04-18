#include "Cmd.hpp"
#include "Reply.hpp"

void cmd::acceptInvite(const int fd, const std::string &target) {
	RPL::send_(fd, "JOIN " + target + "\r\n");
}

// void cmd::answer(const int fd, const std::string &target) {}

void cmd::disconnect(Bot &bot) {
	for (stringVec::const_iterator it = bot.getMembers().begin();
		 it != bot.getMembers().end(); ++it) {
		if (*it != "ft-friend")
			RPL::send_(bot.getFd(), KICK(*it));
	}
	RPL::send_(bot.getFd(), "QUIT\r\n");
}

static bool isLowercase(const std::string &login) {
	for (std::string::const_iterator it = login.begin(); it != login.end();
		 ++it) {
		if (!islower(*it)) {
			if (*it != '-')
				return false;
		}
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
