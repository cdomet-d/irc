#include "Cmd.hpp"
#include "Reply.hpp"

static bool isLowercase(const std::string &login) {
	for (std::string::const_iterator it = login.begin(); it != login.end();
		 ++it) {
		// '-' replaces spaces in composite last names at 42 and so must be allowed
		if (!islower(*it) && *it != '-')
			return false;
	}
	return true;
}

void cmd::man(Bot &bot, const std::string &target) {
	RPL::send_(bot.getFd(), MAN(target));
}

void cmd::acceptInvite(const int fd, const std::string &target) {
	RPL::send_(fd, "JOIN " + target + "\r\n");
}

void cmd::disconnect(Bot &bot) {
	RPL::send_(bot.getFd(), "PRIVMSG #where-friends :Bye! I'm closing the channel!\r\n");
	for (stringVec::const_iterator it = bot.getMembers().begin();
		 it != bot.getMembers().end(); ++it) {
		if (*it != BOT)
			RPL::send_(bot.getFd(), KICK(*it));
	}
	bot.clearMembers();
	bot.setSignal(true);
	RPL::send_(bot.getFd(), QUIT);
}

/* ensures that the leading ! is present and that the login is composed of 
lowercase characters or '-' ; removes leading :! */
bool cmd::parseLogin(std::string &login) {
	if (login.empty() || login.size() > 9 || login.size() < 2)
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
