#include "Bot.hpp"
#include "Reply.hpp"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <unistd.h>

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */
Bot::Bot(int port, std::string pw, std::string servIp)
	: log_("bot.log", std::ios::out), port_(port), gSign(false), pw_(pw) {
	sockFd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockFd == -1)
		throw std::runtime_error("Socket init failed");
	serv_.sin_family = AF_INET;
	serv_.sin_port = htons(port_);
	serv_.sin_addr.s_addr = inet_addr(servIp.c_str());
}

Bot::Bot(void) {}

Bot &Bot::operator=(const Bot &rhs) {
	(void)rhs;
	return *this;
}

Bot::Bot(const Bot &rhs) {
	*this = rhs;
}

Bot::~Bot(void) {
	close(sockFd);
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */

Bot &Bot::getInstance(int port, const std::string &pw,
					  const std::string &servIp) {
	static Bot instance(port, pw, servIp);
	return instance;
}

bool Bot::registrationSequence() {
	while (!requestConnection()) {
		if (gSign == true)
			return false;
		sleep(5);
	}
	if (!registration())
		return false;
	if (!createChan())
		return false;
	return true;
}

bool Bot::requestConnection() {
	int res = connect(sockFd, (const struct sockaddr *)&serv_, sizeof(serv_));
	if (res == -1)
		return RPL::log(RPL::ERROR, "Connection to server failed\r\n"), false;
	std::cout << "Bot is up and running!" << std::endl;
	return true;
}

ssize_t Bot::receive() {
	memset(rcvbuf, 0, sizeof(rcvbuf));
	rcv.clear();
	ssize_t bytes = recv(sockFd, rcvbuf, sizeof(rcvbuf) - 1, 0);
	std::cerr << "Received " << bytes << " bytes; errno is " << errno
			  << std::endl;
	if (bytes == -1)
		return -1;
	if (bytes == 0)
		return 0;
	rcv = rcvbuf;
	RPL::log(RPL::GOT, rcv);
	return 1;
}

bool Bot::rplIs(const std::string &expected) const {
	return rcv.find(expected) != std::string::npos;
}

bool Bot::createChan() {
	RPL::send_(sockFd, "JOIN #where-friends\r\n");
	if (!receive())
		return false;
	RPL::send_(sockFd, "TOPIC #where-friends :send me your friends logins and "
					   "I'll tell you where they're sitting !\r\n");
	if (!receive())
		return false;
	if (rplIs(ERR_CHANOPRIVSNEEDED))
		return RPL::log(RPL::ERROR, "Someone stole my channel ! I can't work "
									"in these conditions >:(\r\n"),
			   false;
	return true;
}

bool Bot::registration() {
	std::cout << "Sending registration message" << std::endl;
	RPL::send_(sockFd,
			   "PASS 0\r\nNICK ft-friend\r\nUSER ftfriend 0 * :ftircbot\r\n");
	while (!rplIs(RPL_ENDOFMOTD)) {
		if (!receive())
			return false;
		if (rplIs(ERR_NICKINUSE))
			return RPL::log(RPL::ERROR, "My nickname is already in use :(\r\n"),
				   false;
	}
	return true;
}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */

int Bot::getFd() const {
	return sockFd;
}

bool Bot::getSignal() const {
	return gSign;
}

/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */

void Bot::setSignal(const bool signum) {
	gSign = signum;
}
