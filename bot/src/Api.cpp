/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Api.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:50:43 by csweetin          #+#    #+#             */
/*   Updated: 2025/04/18 16:26:55 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Api.hpp"

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */

Api::Api(void) : cmd_(NULL), envp_(NULL), resFd_(-1) {}

//TODO : faire un setEnvp plutot que d'utiliser ce constructeur ?
//ou voir si dans bot.hpp je peux directement appeler ce constructeu
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
		RPL::log(RPL::ERROR, "secret not found");
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
	std::vector< std::string > cmd;
	cmd.push_back("curl");
	cmd.push_back("-s");
	cmd.push_back("-X");
	cmd.push_back("POST");
	cmd.push_back("--data");
	cmd.push_back("grant_type=client_credentials&client_id=" + clientIUD_ +
				  "&client_secret=" + secret_);
	cmd.push_back(URL_ + "oauth/token");

	if (!executeCmd(cmd))
		return (false);
	time_ = std::time(0); //TODO: tester time
	token_ = findStr("\"access_token\":");
	if (token_.empty()) {
		RPL::log(RPL::ERROR, "failed to generate token");
		return (false);
	}
	token_.erase(0, 1);
	token_.erase(token_.size() - 1, 1);
	return (true);
}

bool Api::requestLocation(const std::string &login) {
	std::vector< std::string > cmd;
	cmd.push_back("curl");
	cmd.push_back("-s");
	cmd.push_back("-H");
	cmd.push_back("Authorization: Bearer " + token_);
	cmd.push_back(URL_ + "v2/users/" + login);

	if (!executeCmd(cmd))
		return (false);
	std::string user_id;
	user_id = findStr("\"id\":");
	if (user_id.empty())
		return (false);

	cmd.pop_back();
	cmd.push_back(URL_ + "v2/locations?user_id=" + user_id);
	if (!executeCmd(cmd))
		return (false);
	pos_ = findStr("\"location\":");
	if (pos_.empty() || pos_ == "null")
		return (false);
	pos_.erase(0, 1);
	pos_.erase(pos_.size() - 1, 1);
	return (true);
}

std::string Api::findStr(const std::string &strToFind) {
	std::string str;
	std::ifstream infile_;

	infile_.open("res.txt");
	if (!infile_.is_open()) {
		RPL::log(RPL::ERROR, "could not open file 'res.txt'");
		return ("");
	}
	getline(infile_, str, '\0');
	if (infile_.fail() || infile_.bad()) {
		RPL::log(RPL::ERROR, "Error reading");
		return ("");
	}

	size_t start = str.find(strToFind);
	if (start == std::string::npos) {
		RPL::log(RPL::ERROR, "could not find " + strToFind);
		return ("");
	}
	start += strToFind.length();

	size_t end = str.find(",", start);
	if (end == std::string::npos) {
		RPL::log(RPL::ERROR, "could not find " + strToFind);
		return ("");
	}

	return (str.substr(start, end - start));
}

bool Api::executeCmd(std::vector< std::string > &cmd) {
	int child;

	child = fork();
	if (child == -1) {
		RPL::log(RPL::ERROR, "failed to created child process");
		return (false);
	}
	if (child == 0) {
		if (!findCurlPath())
			exit(errno);
		// cmd.clear();
		// curlPath_.clear();
		// exit(errno);
		if (!openFile())
			exit(errno);
		if (dup2(resFd_, 1) == -1) {
			RPL::log(RPL::ERROR, "redirection failed");
			close(resFd_);
			exit(errno);
		}
		if (!fillCmd(cmd)) {
			close (resFd_);
			exit(errno);
		}
		if (execve(curlPath_.c_str(), cmd_, envp_) == -1)
			RPL::log(RPL::ERROR, "execve failed");
		close(0);
		close(1);
		close(resFd_);
		for (size_t i = 0; cmd_[i]; i++)
			free(cmd_[i]);
		free(cmd_);
		exit(errno);
	}
	int status;
	waitpid(child, &status, 0);
	return (curlStatus(status));
}

bool Api::openFile() {
	resFd_ = open("res.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (resFd_ == -1) {
		RPL::log(RPL::ERROR, "could not open res.txt");
		return (false);
	}
	return (true);
}

bool Api::findCurlPath() {
	std::string pathVar = getEnvVar("PATH=");
	if (pathVar.empty())
		return (false);

	size_t pos = 0;
	for (size_t i = 0; i < pathVar.size(); i++) {
		pos = pathVar.find(":");
		if (pos == std::string::npos)
			pos = pathVar.size();
		curlPath_.assign(pathVar, 0, pos);
		curlPath_ += "/curl";
		if (access(curlPath_.c_str(), X_OK) == 0)
			return (true);
		pathVar.erase(0, i + 1);
		curlPath_.clear();
	}
	RPL::log(RPL::ERROR, "could not find path");
	return (false);
}

bool Api::fillCmd(std::vector< std::string > &cmd) {
	cmd_ = (char **)malloc(sizeof(char *) * (cmd.size() + 1));
	if (cmd_ == NULL)
		return (false);
	for (size_t i = 0; i < cmd.size(); ++i) {
		cmd_[i] = strdup(cmd[i].c_str());
		if (cmd_[i] == NULL) {
			while ((int)i >= 0)
				free(cmd_[i--]);
			free(cmd_);
			RPL::log(RPL::ERROR, "strdup failed");
			return (false);
		}
	}
	cmd_[cmd.size()] = NULL;
	return (true);
}

bool Api::curlStatus(int status) {
	if (WIFEXITED(status)) {
		int exitCode = WEXITSTATUS(status);
		if (exitCode != 0) {
			// RPL::log(RPL::ERROR, "Curl command failed with exit code: " + exitCode);
			return (false);
		}
	} else if (WIFSIGNALED(status)) {
		// int signal = WTERMSIG(status);
		// RPL::log(RPL::ERROR, "Curl process terminated by signal: " + signal);
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
