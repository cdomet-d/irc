/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:39 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/20 12:42:39 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <cerrno>
#include <sstream>

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */

Server::Server(int port, std::string password)
	: logfile("raw.log", std::ios::out | std::ios::app), port_(port),
	  pass_(password) {
	std::cout << "Server instance created" << std::endl;
}

Server::~Server(void) {
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
	servPoll_.events = POLLIN;
	if (epoll_ctl(epollFd_, EPOLL_CTL_ADD, servFd_, &servPoll_) == -1)
		return 0;
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
			else if (handleData(events_[i].data.fd) == false)
				return true;
		}
	}
	return (true);
}

void Server::acceptClient() {
	try {
		Client *newCli = new Client();
		newCli->cliInfo.setRegistration(3);

		struct epoll_event cliEpollTemp;
		socklen_t cliLen = sizeof(newCli->cliAddr_);
		newCli->setFd(
			accept(servFd_, (struct sockaddr *)&newCli->cliAddr_, &cliLen));

		if (newCli->getFd() == -1)
			throw Server::InitFailed(
				const_cast< const char * >(strerror(errno)));

		char client_ip[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &(newCli->cliAddr_.sin_addr), client_ip,
				  INET_ADDRSTRLEN);
		newCli->cliInfo.setIP(client_ip);

		char hostname[NI_MAXHOST];
		int result = getnameinfo((struct sockaddr *)&newCli->cliAddr_, cliLen,
								 hostname, NI_MAXHOST, NULL, 0, 0);
		if (result == 0) {
			newCli->cliInfo.setHostname(hostname);
		} else {
			newCli->cliInfo.setHostname(client_ip); // Use IP as fallback
		}
		//TODO: not throw an exeption when a client cannot connect: it can't kill the server.
		if (fcntl(newCli->getFd(), F_SETFL, O_NONBLOCK) == -1) {
			close(newCli->getFd());
			throw Server::InitFailed(
				const_cast< const char * >(strerror(errno)));
		}
		cliEpollTemp.events = EPOLLIN;
		cliEpollTemp.data.fd = newCli->getFd();
		newCli->setCliEpoll(cliEpollTemp);

		if (epoll_ctl(epollFd_, EPOLL_CTL_ADD, newCli->getFd(),
					  newCli->getCliEpoll()) == -1) {
			close(newCli->getFd());
			throw Server::InitFailed(
				const_cast< const char * >(strerror(errno)));
		}

		clients_.insert(clientPair(newCli->getFd(), newCli));
		usedNicks_.insert(nickPair(newCli->cliInfo.getNick(), newCli->getFd()));
		std::stringstream ss;
		ss << "Client [" << newCli->getFd() << "] connected";
	} catch (std::exception &e) { std::cerr << e.what() << std::endl; }
}

bool Server::handleData(int fd) {
	char tmpBuf[1024];
	memset(tmpBuf, 0, sizeof(tmpBuf));
	ssize_t bytes = recv(fd, tmpBuf, sizeof(tmpBuf) - 1, 0);

	Client *curCli = clients_.find(fd)->second;
	if (bytes <= 0)
		return (disconnectCli(fd));
	else {
		std::string inputCli = curCli->mess.getBuffer();
		inputCli.append(tmpBuf);
		curCli->mess.setBuffer(inputCli);
		messageValidator::assess(*curCli);
		curCli->mess.clearBuffer();
		curCli->mess.clearCmdParam();
	}
	return (true);
}

// void Server::processBuffer(Client *curCli) {
// 	size_t pos;
// 	while ((pos = curCli->mess.getBuffer().find('\n')) != std::string::npos) {
// 		if (!curCli->mess.getBuffer().find("QUIT")) {
// 			std::cout << "Exit server" << std::endl;
// 			disconnectCli(curCli->getFd());
// 			return;
// 		}
// 		if (curCli->mess.getBuffer().find("CAP LS") != std::string::npos ||
// 			curCli->mess.getBuffer().find("NICK") != std::string::npos ||
// 			curCli->mess.getBuffer().find("USER") != std::string::npos) {
// 			handleClientRegistration(curCli->mess.getBuffer(), curCli);
// 			curCli->mess.setBuffer("");
// 			return;
// 		} else {
// 			curCli->mess.setBuffer("");
// 			return;
// 		}
// 	}
// }

bool checkOnlyOperator(int fd) {
	static Server &server = Server::GetServerInstance(0, "");

	clientMap::const_iterator curCli = server.getAllCli().find(fd);
	//joinExec("0", curCli->second);
	for (stringVec::iterator curChanName =
			 curCli->second->getJoinedChans().begin();
		 curChanName != curCli->second->getJoinedChans().end();
		 ++curChanName) {
		channelMapIt curChan = server.getAllChan().find(*curChanName);
		if (!curChan->second->getOpCli().size()) {
			if (curChan->second->getCliInChan().size() >= 1) {
				curChan->second->addCli(OPCLI, curChan->second->getCliInChan().begin()->second);
				return (true);
			}
			//delete chan if the disconnected cli was the one cli in chan
			if (curChan->second->getCliInChan().empty() == true) {
				server.removeChan(curChan->second);
				delete curChan->second;
			}
		}
	}
	return (false);
}

bool Server::disconnectCli(int fd) {
	checkOnlyOperator(fd);
	clientMapIt it = clients_.find(fd);
	if (it != clients_.end()) {
		std::stringstream ss;
		ss << "Client [" << it->second->getFd() << "] connected";
		reply::log(reply::INFO, ss.str());
		delete it->second;
		clients_.erase(fd);
		close(fd);
		return true;
	}
	return false;
}
/* ************************************************************************** */
/*                               EXCEPTIONS                                   */
/* ************************************************************************** */

const char *Server::InitFailed::what() const throw() {
	std::cerr << "irc: ";
	return errMessage;
}

Server::InitFailed::InitFailed(const char *err) : errMessage(err) {}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */
const clientMap &Server::getAllCli() const
{
	return (clients_);
}
const channelMap &Server::getAllChan() const
{
	return (channels_);
}

const nickMap &Server::getUsedNick() const {
	return (usedNicks_);
}

int Server::getFdFromNick(const std::string &nick) const {
	nickMap::const_iterator nickInMap = usedNicks_.find(nick);
	if (nickInMap != usedNicks_.end())
		return nickInMap->second;
	return -1;
}

const std::string Server::getPass() const {
	return (pass_);
}
