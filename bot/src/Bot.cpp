#include "Bot.hpp"
#include "Cmd.hpp"
#include "Reply.hpp"
#include <algorithm>
#include <iostream>

void cmdParam(const stringVec &obj, std::string where) {
	if (obj.empty())
		return std::cout << where + ": [ ... ]" << std::endl, (void)false;
	std::cout << "[" << std::endl;
	for (stringVec::const_iterator it = obj.begin(); it != obj.end(); ++it) {
		if ((*it).empty())
			std::cout << "\t" + where + ":\t" << "[...]" << std::endl;
		else
			std::cout << "\t" + where + ":\t" << *it << std::endl;
	}
	std::cout << "]" << std::endl;
}

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */
Bot::Bot(int port, std::string pw, std::string servIp, char *envp[])
	: log_("bot.log", std::ios::out), api(Api (envp)), port_(port), gSign(false), pw_(pw) {
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
					  const std::string &servIp, char *envp[]) {
	static Bot instance(port, pw, servIp, envp);
	return instance;
}

bool Bot::executeCmd() {
	msg.processBuf();
	cmdParam(msg.cmdParam_, "After process");
	if (msg.cmdParam_[cmd_] == "INVITE")
	cmd::join(sockFd, msg.cmdParam_[msg_]);
	else if (msg.cmdParam_[cmd_] == "PRIVMSG") {
		if (msg.cmdParam_[msg_] == ":bye") {
			cmd::disconnect(sockFd);
			return false;
		}
		if (!cmd::parseLogin(msg.cmdParam_[msg_])) {
			std::cerr << "wrong login: " << msg.cmdParam_[msg_] << std::endl;
			return RPL::send_(sockFd,
					   "PRIVMSG " + msg.cmdParam_[target_] +
						   ": login format is incorrect; should be !<[a - "
						   "z]>; max len 9, is " +
						   msg.cmdParam_[msg_] + "\r\n"), false;
		}
		if (!findLoginPos(msg.cmdParam_[msg_])) {
			RPL::send_(sockFd, "location not found for " + msg.cmdParam_[msg_]);
			return (false);
		}
		RPL::send_(sockFd, api.getPos());
		// std::cout << "position:" << api.getPos() << std::endl;
	}
	return true;
}

bool Bot::findLoginPos(const std::string &login) {
	if (!api.findSecret())
		return (false);
	if (!api.requestToken())
		return (false);	
	if (!api.requestLocation(login))
		return (false);
	return (true);
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

bool Bot::createChan() {
	RPL::send_(sockFd, "JOIN #where-friends\r\n");
	if (!receive())
		return false;
	RPL::send_(sockFd, "TOPIC #where-friends :send me your friends logins and "
					   "I'll tell you where they're sitting !\r\n");
	if (!receive())
		return false;
	if (msg.rplIs(ERR_CHANOPRIVSNEEDED))
		return RPL::log(RPL::ERROR, "Someone stole my channel ! I can't work "
									"in these conditions >:(\r\n"),
			   false;
	return true;
}

bool Bot::registration() {
	std::cout << "Sending registration message" << std::endl;
	RPL::send_(sockFd,
			   "PASS 0\r\nNICK ft-friend\r\nUSER ftfriend 0 * :ftircbot\r\n");
	while (!msg.rplIs(RPL_ENDOFMOTD)) {
		if (!receive())
			return false;
		if (msg.rplIs(ERR_NICKINUSE))
			return RPL::log(RPL::ERROR, "My nickname is already in use :(\r\n"),
				   false;
	}
	return true;
}

ssize_t Bot::receive() {
	msg.clear();
	ssize_t bytes = msg._recv(sockFd);
	if (bytes == -1)
		return -1;
	if (bytes == 0)
		return 0;
	msg.setRcv();
	RPL::log(RPL::GOT, msg.getRcv());
	return bytes;
}

bool Bot::run() {
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
