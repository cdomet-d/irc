#ifndef CMD_HPP
#define CMD_HPP

#include "Bot.hpp"
#include <string>

namespace cmd {
	void acceptInvite(const int fd, const std::string &target);
	void disconnect(Bot &bot);
	bool parseLogin(std::string &login);
} // namespace cmd

#endif
