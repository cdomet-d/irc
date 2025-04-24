#include "Cmd.hpp"
#include "Bot.hpp"
#include "Reply.hpp"

void cmd::man(Bot &bot, const std::string &target) {
	RPL::send_(bot.getFd(), MAN(target));
}

void cmd::acceptInvite(const int fd, const std::string &target) {
	RPL::send_(fd, "JOIN " + target + "\r\n");
}

void cmd::disconnect(Bot &bot) {
	RPL::send_(bot.getFd(),
			   "PRIVMSG #where-friends :Bye! I'm closing the channel!\r\n");
	for (stringVec::const_iterator it = bot.getMembers().begin();
		 it != bot.getMembers().end(); ++it) {
		if (*it != BOT) {
			RPL::send_(bot.getFd(), KICK(*it));
			if (!bot.receive())
				return;
		}
	}
	sleep(1);
	bot.clearMembers();
	bot.setSignal(true);
	RPL::send_(bot.getFd(), QUIT);
}

/* ensures that the leading ! is present; removes leading :! */
bool cmd::parseLogin(std::string &login) {
	if (login.empty() || login.size() > 10 || login.size() < 2)
		return false;
	if (login.at(0) == ':')
		login.erase(login.begin());
	if (login.at(0) != '!')
		return false;
	login.erase(login.begin());
	return true;
}
