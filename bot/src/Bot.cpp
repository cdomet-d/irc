#include "Bot.hpp"

Bot::Bot(int port, std::string pw) : port_(port), pw_(pw) {}


Bot &Bot::getInstance(int port, const std::string &pw) {
	static Bot instance(port, pw);
	return instance;
}