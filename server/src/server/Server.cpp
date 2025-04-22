/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:39 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/22 16:47:58 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "CmdExecution.hpp"
#include "Reply.hpp"
#include "printers.hpp"
#include <cerrno>
#include <sstream>

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */

Server::Server(int port, std::string password)
	: logfile("serv_.log", std::ios::out), port_(port), pass_(password) {
	std::cout << "Server instance created" << std::endl;
}

Server::~Server() {
	std::cout << "Calling destructor" << std::endl;
	logfile.close();
	for (clientMapIt it = clients_.begin(); it != clients_.end(); ++it) {
		it->second->cliInfo.getNick().clear();
		it->second->cliInfo.getUsername().clear();
		close(it->first);
		delete it->second;
	}
	for (channelMapIt it = channels_.begin(); it != channels_.end(); ++it)
		delete it->second;

	close(epollFd_);
	close(servFd_);
}

Server &Server::GetServerInstance(int port, std::string password) {
	static Server instance(port, password);
	return (instance);
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */

bool Server::servInit() {
	int en = 1;

	epollFd_ = epoll_create1(0);
	if (epollFd_ == -1)
		return (false);
	servAddr_.sin_family = AF_INET;
	servAddr_.sin_port = htons(port_);
	servAddr_.sin_addr.s_addr = INADDR_ANY;

	servFd_ = socket(AF_INET, SOCK_STREAM, 0);

	if (setsockopt(servFd_, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) == -1)
		return (false);
	if (fcntl(servFd_, F_SETFL, O_NONBLOCK) == -1)
		return (false);
	if (bind(servFd_, (struct sockaddr *)&servAddr_, sizeof(servAddr_)) == -1)
		return (false);
	if (listen(servFd_, SOMAXCONN) == -1)
		return (false);
	servPoll_.data.fd = servFd_;
	servPoll_.events = EPOLLIN | EPOLLOUT;
	if (epoll_ctl(epollFd_, EPOLL_CTL_ADD, servFd_, &servPoll_) == -1)
		return (0);
	return (true);
}

bool Server::servRun() {
	int nbFds;

	std::cout << "Server listening on port " << port_
			  << " | IP adress: " << inet_ntoa(servAddr_.sin_addr) << std::endl;
	while (gSign == false) {
		nbFds = epoll_wait(epollFd_, events_, MAX_EVENTS, -1);
		if (nbFds == -1 && gSign == false)
			return (false);
		for (int i = 0; i < nbFds; i++) {
			if (events_[i].data.fd == servFd_)
				acceptClient();
			else
				handleData(events_[i].data.fd);
		}
	}
	return (true);
}

void Server::acceptClient() {
	try {
		Client *newCli = new Client();
		newCli->cliInfo.setRegistration(0);

		struct epoll_event cliEpollTemp;
		socklen_t cliLen = sizeof(newCli->cliAddr_);
		newCli->setFd(
			accept(servFd_, (struct sockaddr *)&newCli->cliAddr_, &cliLen));

		if (newCli->getFd() == -1)
			throw Server::InitFailed(
				const_cast< const char * >(std::strerror(errno)));

		char *client_ip = inet_ntoa(newCli->cliAddr_.sin_addr);
		if (!client_ip) {
			close(newCli->getFd());
			throw Server::InitFailed("IP conversion failed");
		}
		newCli->cliInfo.setIP(client_ip);
		newCli->cliInfo.setHostname("localhost");
		// TODO: not throw an exeption when a client cannot connect: it can't kill
		// the server.
		if (fcntl(newCli->getFd(), F_SETFL, O_NONBLOCK) == -1) {
			close(newCli->getFd());
			throw Server::InitFailed(
				const_cast< const char * >(std::strerror(errno)));
		}
		cliEpollTemp.events = EPOLLIN | EPOLLOUT;
		cliEpollTemp.data.fd = newCli->getFd();
		newCli->setCliEpoll(cliEpollTemp);

		if (epoll_ctl(epollFd_, EPOLL_CTL_ADD, newCli->getFd(),
					  newCli->getCliEpoll()) == -1) {
			close(newCli->getFd());
			throw Server::InitFailed(
				const_cast< const char * >(std::strerror(errno)));
		}

		clients_.insert(clientPair(newCli->getFd(), newCli));
		usedNicks_.insert(nickPair(newCli->cliInfo.getNick(), newCli->getFd()));
		std::stringstream ss;
		ss << "Client [" << newCli->getFd() << "] connected\n";
		RPL::log(RPL::INFO, ss.str());
	} catch (std::exception &e) { std::cerr << e.what() << std::endl; }
}

void Server::handleData(int fd) {
	char tmpBuf[1024];
	std::memset(tmpBuf, 0, sizeof(tmpBuf));
	ssize_t bytes = recv(fd, tmpBuf, sizeof(tmpBuf) - 1, MSG_DONTWAIT);

	Client *curCli = clients_.find(fd)->second;
	if (bytes == 0) {
		curCli->mess.setMess("QUIT\n");
		buffer_manip::prepareCommand(*curCli);
		return;
	} else if (bytes == -1)
		return;
	else {
		std::string inputCli = curCli->mess.getMess();
		inputCli.append(tmpBuf);
		curCli->mess.setMess(inputCli);
		if (curCli->mess.getMess().find('\n') != std::string::npos) {
			RPL::log(RPL::GOT, curCli->mess.getMess());
			buffer_manip::prepareCommand(*curCli);
		}
	}
}

void Server::addChan(Channel *curChan) {
	channels_.insert(
		std::pair< std::string, Channel * >(curChan->getName(), curChan));
}

void Server::removeChan(Channel *curChan) {
	channels_.erase(curChan->getName());
}
void Server::removeCli(Client *curCli) {
	removeNickFromUsedNicks(curCli->cliInfo.getNick());
	clients_.erase(curCli->getFd());
}

void Server::checkChanInviteList(Client *sender) {
	for (channelMapIt chan = channels_.begin(); chan != channels_.end();
		 ++chan) {
		if (chan->second->getInvitCli().find(sender->getFd()) !=
			chan->second->getInvitCli().end())
			RPL::send_(sender->getFd(),
					   RPL_INVITELIST(sender->cliInfo.getNick(), chan->first));
	}
	RPL::send_(sender->getFd(), RPL_ENDOFINVITELIST(sender->cliInfo.getNick()));
}

Client *Server::findCli(int fd) {
	clientMapIt currCliIt = clients_.find(fd);
	if (currCliIt == clients_.end())
		return (NULL);
	return (currCliIt->second);
}

Channel *Server::findChan(std::string chanName) {
	channelMapIt currChanIt = channels_.find(chanName);
	if (currChanIt == channels_.end())
		return (NULL);
	return (currChanIt->second);
}

void Server::addNickToUsedNicks(const std::string &newNick, int fd) {
	usedNicks_.insert(nickPair(newNick, fd));
}

void Server::removeNickFromUsedNicks(const std::string &toRemove) {
	nickMap::iterator nickToRm = usedNicks_.find(toRemove);
	if (nickToRm == usedNicks_.end())
		return;
	usedNicks_.erase(nickToRm);
}

/* ************************************************************************** */
/*                               EXCEPTIONS                                   */
/* ************************************************************************** */

const char *Server::InitFailed::what() const throw() {
	std::cerr << "irc: ";
	return (errMessage);
}

Server::InitFailed::InitFailed(const char *err) : errMessage(err) {}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */

const clientMap &Server::getAllCli() const {
	return (clients_);
}
const channelMap &Server::getAllChan() const {
	return (channels_);
}

const nickMap &Server::getUsedNick() const {
	return (usedNicks_);
}

int Server::getFdFromNick(const std::string &nick) const {
	nickMap::const_iterator nickInMap = usedNicks_.find(nick);
	if (nickInMap != usedNicks_.end())
		return nickInMap->second;
	return (-1);
}

const std::string Server::getPass() const {
	return (pass_);
}
