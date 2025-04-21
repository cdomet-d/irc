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
Bot::Bot(int port, std::string pw, std::string servIp)
	: log_("bot.log", std::ios::out), myChan_("#where-friends"), port_(port), gSign(false), pw_(pw) {
	sockFd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockFd == -1)
		throw std::runtime_error("Socket init failed");
	serv_.sin_family = AF_INET;
	serv_.sin_port = htons(port_);
	serv_.sin_addr.s_addr = inet_addr(servIp.c_str());
	if (serv_.sin_addr.s_addr == INADDR_NONE)
		throw std::runtime_error("InvalidIpv4 address");
}

Bot::Bot(void) {}

Bot::~Bot(void) {
	close(sockFd);
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */
void Bot::clearMembers() {
	members_.clear();
}

Bot &Bot::getInstance(int port, const std::string &pw,
					  const std::string &servIp) {
	static Bot instance(port, pw, servIp);
	return instance;
}

bool Bot::executeCmd() {
	msg_.processBuf();
	if (msg_.cmdParam_.size() < content_)
		RPL::send_(sockFd, "Message is malformed");
	const std::string target = getTarget();
	
	if (msg_.cmdParam_[cmd_] == "INVITE")
		cmd::acceptInvite(sockFd, msg_.cmdParam_[content_]);
	if (msg_.cmdParam_[cmd_] == "JOIN")
		addClient(msg_.cmdParam_[prefix_]);
	else if (msg_.cmdParam_[cmd_] == "PRIVMSG") {
		if (msg_.cmdParam_[content_] == ":bye")
			return cmd::disconnect(*this), false;
		if (msg_.cmdParam_[content_] == ":!man")
			return cmd::man(*this, target), false;
		if (!cmd::parseLogin(msg_.cmdParam_[content_]))
			return RPL::send_(sockFd,
							  ERR_INVALIDSYNTAX(target, msg_.cmdParam_[content_])),
				   false;
		RPL::send_(sockFd, RPL_SUCCESS(target, msg_.cmdParam_[content_]));
	}
	return true;
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
	RPL::send_(sockFd, JOIN(myChan_));
	RPL::send_(sockFd, TOPIC);
	if (!receive())
		return false;
	if (msg_.rplIs(ERR_CHANOPRIVSNEEDED))
		return RPL::log(RPL::ERROR, ERR_CANNOTCREATECHAN), false;
	return true;
}

bool Bot::registration() {
	RPL::send_(sockFd, REGISTER);
	while (!msg_.rplIs(RPL_ENDOFMOTD)) {
		if (!receive())
			return false;
		if (msg_.rplIs(ERR_NICKINUSE))
			return RPL::log(RPL::ERROR, ERR_CANNOTREGISTER), false;
	}
	return true;
}

ssize_t Bot::receive() {
	msg_.clear();
	ssize_t bytes = msg_._recv(sockFd);
	if (bytes == -1)
		return -1;
	if (bytes == 0)
		return 0;
	msg_.setRcv();
	RPL::log(RPL::GOT, msg_.getRcv());
	return bytes;
}

void Bot::addClient(const std::string &nick) {
	members_.push_back(nick);
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
	return members_;
}

const std::string Bot::getTarget() const {
	return (msg_.cmdParam_[target_] == BOT ? msg_.cmdParam_[prefix_]
										  : msg_.cmdParam_[target_]);
}

/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */

void Bot::setSignal(const bool signum) {
	gSign = signum;
}
