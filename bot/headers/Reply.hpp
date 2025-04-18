#ifndef REPLY_HPP
#define REPLY_HPP

#include <string>

namespace RPL {
enum e_level { INFO, ERROR, DEBUG, REPLY, GOT };
void log(e_level level, std::string message, std::string verbose);
void log(e_level level, std::string message);
void send_(int fd, std::string reply);

} // namespace RPL

#define ERR_NICKINUSE "433"
#define RPL_ENDOFMOTD "376"
#define ERR_CHANOPRIVSNEEDED "482"

#define ERR_INVALIDSYNTAX(target, login)                                       \
	"PRIVMSG " + target + " :invalid syntax: should be !<[a - z]>, is " +      \
		login + "\r\n"
#define ERR_TOOLONG(target) "PRIVSMG " + target + " :len should be < 9\r\n"
#define ERR_CANNOTCREATECHAN                                                   \
	"Someone stole my channel ! I can't work in these conditions >:(\r\n"
#define ERR_CANNOTREGISTER "My nickname is already in use :(\r\n"

#define RPL_SUCCESS(target, login)                                             \
	"PRIVMSG " + target + " :" + login + " is a valid login, fetching...\r\n"
#define ERR_NOLOCATION(target, login)                                          \
	"PRIVMSG " + target + " :Location not found for " + login + "\r\n"
#define RPL_LOCATION(target, location) "PRIVMSG " + target + " :" + location + "\r\n"

#define KICK(nick) "KICK #where-friends " + nick + "\r\n"
#define TOPIC "TOPIC #where-friends : do !commands to see how to invoke me!\r\n"
#define JOIN "JOIN #where-friends\r\n"
#define REGISTER "PASS 0\r\nNICK ft-friend\r\nUSER ftfriend 0 * :ftircbot\r\n"
#endif