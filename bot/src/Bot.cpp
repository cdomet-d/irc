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
	if (msg.cmdParam_[cmd_] == "INVITE")
		cmd::acceptInvite(sockFd, msg.cmdParam_[msg_]);
	if (msg.cmdParam_[cmd_] == "JOIN")
		addClient(msg.cmdParam_[prefix_]);
	else if (msg.cmdParam_[cmd_] == "PRIVMSG") {
		if (msg.cmdParam_[msg_] == ":bye")
			return cmd::disconnect(*this), false;
		std::string target =
			(msg.cmdParam_[target_] == "ft-friend" ? msg.cmdParam_[prefix_]
												   : msg.cmdParam_[target_]);
		if (!cmd::parseLogin(msg.cmdParam_[msg_]))
			return RPL::send_(sockFd,
							  ERR_INVALIDSYNTAX(target, msg.cmdParam_[msg_])),
				   false;
		if (!findLoginPos(msg.cmdParam_[msg_])) {
			RPL::send_(sockFd, "location not found for " + msg.cmdParam_[msg_]);
			return (false);
		}
		RPL::send_(sockFd, RPL_SUCCESS(target, msg.cmdParam_[msg_]));
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
		if (gSign)
			return false;
		close(sockFd);
		sockFd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockFd == -1)
			throw std::runtime_error("Socket init failed");	
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
	RPL::send_(sockFd, JOIN);
	RPL::send_(sockFd, TOPIC);
	if (!receive())
		return false;
	if (msg.rplIs(ERR_CHANOPRIVSNEEDED))
		return RPL::log(RPL::ERROR, ERR_CANNOTCREATECHAN), false;
	return true;
}

bool Bot::registration() {
	RPL::send_(sockFd, REGISTER);
	while (!msg.rplIs(RPL_ENDOFMOTD)) {
		if (!receive())
			return false;
		if (msg.rplIs(ERR_NICKINUSE))
			return RPL::log(RPL::ERROR, ERR_CANNOTREGISTER), false;
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

void Bot::addClient(const std::string &nick) {
	chanMembers.push_back(nick);
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

const stringVec &Bot::getMembers() const {
	return chanMembers;
}

/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */

void Bot::setSignal(const bool signum) {
	gSign = signum;
}
