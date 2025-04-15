#include "Bot.hpp"
#include "Reply.hpp"
#include <unistd.h>
#include <iostream>

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */
Bot::Bot(int port, std::string pw, std::string servIp)
	: log_("bot.log", std::ios::out), port_(port), pw_(pw) {
	std::cout << "Bot is up and running!" << std::endl;
	sockFd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockFd == -1)
		throw std::runtime_error("Socket init failed");
	serv_.sin_family = AF_INET;
	serv_.sin_port = htons(port_);
	serv_.sin_addr.s_addr = inet_addr(servIp.c_str());
	std::cout << "Bot socket: " << sockFd << std::endl
			  << "Port: " << serv_.sin_port << std::endl
			  << "Server IP: " << serv_.sin_addr.s_addr << std::endl;
}

Bot::Bot(void) {
	close(sockFd);
}

Bot &Bot::operator=(const Bot &rhs) {
	(void)rhs;
	return *this;
}

Bot::Bot(const Bot &rhs) {
	*this = rhs;
}


Bot::~Bot(void) {}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */

Bot &Bot::getInstance(int port, const std::string &pw,
					  const std::string &servIp) {
	static Bot instance(port, pw, servIp);
	return instance;
}

bool Bot::requestConnection() {

	int res = connect(sockFd, (const struct sockaddr *)&serv_, sizeof(serv_));
	if (res == -1) 
		return RPL::log(RPL::ERROR, "Connection to server failed"), false;
	return true;
}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */

int Bot::getFd() const {
	return sockFd;
}


/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */