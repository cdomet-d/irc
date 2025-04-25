/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Api.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:50:43 by csweetin          #+#    #+#             */
/*   Updated: 2025/04/25 10:00:27 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Api.hpp"

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */

Api::Api(void) : cmd_(NULL), envp_(NULL), resFd_(-1) {}

Api::Api(char **envp)
	: cmd_(NULL), envp_(envp), resFd_(-1),
	  clientIUD_(
		  "u-s4t2ud-"
		  "ad20c0580b5b2d1e67736549dd536f87146a2340a5cbd41aba0c1da8655e0293"),
	  URL_("https://api.intra.42.fr/") {}

Api::Api(const Api &rhs) {
	*this = rhs;
}

Api::~Api(void) {}

Api &Api::operator=(const Api &rhs) {
	if (this != &rhs) {
		clientIUD_ = rhs.clientIUD_;
		URL_ = rhs.URL_;
	}
	return *this;
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */
bool Api::findSecret() {
	secret_ = getEnvVar("IRCBOT_SECRET=");
	if (secret_.empty()) {
		RPL::log(RPL::ERROR, "secret not found\r\n");
		return (false);
	}
	return (true);
}

bool Api::requestToken() {
	if (!token_.empty()) {
		std::time_t temp = std::time(0);
		if (temp - time_ < 7200)
			return (true);
	}
	curlCmd_.reserve(7);
	curlCmd_.push_back("curl");
	curlCmd_.push_back("-s");
	curlCmd_.push_back("-X");
	curlCmd_.push_back("POST");
	curlCmd_.push_back("--data");
	curlCmd_.push_back("grant_type=client_credentials&client_id=" + clientIUD_ +
					   "&client_secret=" + secret_);
	curlCmd_.push_back(URL_ + "oauth/token");

	if (!executeCmd())
		return (false);
	time_ = std::time(0);
	token_ = findStr("\"access_token\":");
	if (token_.empty()) {
		RPL::log(RPL::ERROR, "failed to generate token\r\n");
		return (false);
	}
	token_.erase(0, 1);
	token_.erase(token_.size() - 1, 1);
	return (true);
}

bool Api::requestLocation(const int fd, const std::string &target, const std::string &login) {
	curlCmd_.clear();
	curlCmd_.push_back("curl");
	curlCmd_.push_back("-s");
	curlCmd_.push_back("-H");
	curlCmd_.push_back("Authorization: Bearer " + token_);
	curlCmd_.push_back(URL_ + "v2/users/" + login);

	if (!executeCmd())
		return (false);
	pos_ = findStr("\"location\":");
	if (pos_.empty())
		return RPL::send_(fd, ERR_NOSUCHLOGIN(target, login)), false;
	if (pos_ == "null")
		return RPL::send_(fd, ERR_NOLOCATION(target, login)), false;
	pos_.erase(0, 1);
	pos_.erase(pos_.size() - 1, 1);
	return (true);
}

std::string Api::findStr(const std::string &strToFind) {
	std::string str;
	std::ifstream infile_;

	infile_.open("res.txt");
	if (!infile_.is_open()) {
		RPL::log(RPL::ERROR, "could not open res.txt\r\n");
		return ("");
	}
	getline(infile_, str, '\0');
	if (infile_.fail() || infile_.bad()) {
		RPL::log(RPL::ERROR, "could not read res.txt\r\n");
		return ("");
	}

	size_t start = str.find(strToFind);
	if (start == std::string::npos) {
		RPL::log(RPL::ERROR, "could not find " + strToFind + "\r\n");
		return ("");
	}
	start += strToFind.length();

	size_t end = str.find(",", start);
	if (end == std::string::npos) {
		RPL::log(RPL::ERROR, "could not find " + strToFind + "\r\n");
		return ("");
	}

	return (str.substr(start, end - start));
}

bool Api::executeCmd(void) {
	int child;

	child = fork();
	if (child == -1) {
		RPL::log(RPL::ERROR, "failed to create child process\r\n");
		return (false);
	}
	if (child == 0) {
		if (!findCurlPath())
			cleanChild(EXIT_FAILURE);
		if (!openFile())
			cleanChild(EXIT_FAILURE);
		if (dup2(resFd_, 1) == -1) {
			RPL::log(RPL::ERROR, "redirection failed\r\n");
			cleanChild(EXIT_FAILURE);
		}
		if (!fillCmd())
			cleanChild(EXIT_FAILURE);
		execve(curlPath_.c_str(), cmd_, envp_);
		RPL::log(RPL::ERROR, "execve failed\r\n");
		cleanChild(errno);
	}
	int status = 0;
	if (waitpid(child, &status, 0) == -1) {
		RPL::log(RPL::ERROR, "waitpid failed\r\n");
		return (false);
	}
	return (curlStatus(status));
}

void Api::cleanChild(int exitCode) {
	if (resFd_ != -1)
		close(resFd_);
	if (cmd_ != NULL)
		delete[] cmd_;
	close(0);
	close(1);
	curlCmd_.clear();
	curlPath_.clear();
	std::exit(exitCode);
}

bool Api::openFile() {
	resFd_ = open("res.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (resFd_ == -1) {
		RPL::log(RPL::ERROR, "could not create/open res.txt\r\n");
		return (false);
	}
	return (true);
}

bool Api::findCurlPath() {
	std::string pathVar = getEnvVar("PATH=");
	if (pathVar.empty()) {
		RPL::log(RPL::ERROR, "could not find path\r\n");
		return (false);
	}
	stringVec paths = vectorSplit(pathVar, ':');
	for (size_t i = 0; i < paths.size(); i++) {
		curlPath_ = paths[i] + "/curl";
		if (access(curlPath_.c_str(), X_OK) == 0)
			return (true);
		curlPath_.clear();
	}
	RPL::log(RPL::ERROR, "could not find path\r\n");
	return (false);
}

bool Api::fillCmd(void) {
	cmd_ = new char *[curlCmd_.size() + 1];
	for (size_t i = 0; i < curlCmd_.size(); ++i)
		cmd_[i] = const_cast< char * >(curlCmd_[i].c_str());
	cmd_[curlCmd_.size()] = NULL;
	return (true);
}

bool Api::curlStatus(int status) {
	if (WIFEXITED(status)) {
		int exitCode = WEXITSTATUS(status);
		if (exitCode != 0) {
			std::string errorMess = std::strerror(exitCode);
			RPL::log(RPL::ERROR, "Curl command failed: " + errorMess + "\r\n");
			return (false);
		}
	} else if (WIFSIGNALED(status)) {
		RPL::log(RPL::ERROR, "Curl process terminated by signal\r\n");
		return (false);
	}
	return (true);
}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */
std::string Api::getEnvVar(const std::string &varName) {
	for (size_t i = 0; envp_[i]; i++) {
		if (!std::strncmp(envp_[i], varName.c_str(), varName.size())) {
			return (envp_[i] + varName.size());
		}
	}
	return ("");
}

const std::string &Api::getPos(void) const {
	return (pos_);
}

/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */
