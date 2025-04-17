/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Api.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:50:43 by csweetin          #+#    #+#             */
/*   Updated: 2025/04/16 18:43:19 by csweetin         ###   ########.fr       */
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
//TODO: mettre les erreurs dans le rawlog

bool Api::findSecret() {
	secret_ = getEnvVar("IRCBOT_SECRET=");
	if (secret_.empty()) {
		std::cerr << "Error: secret not found\n";
		return (false);
	}
	return (true);
}

bool Api::generateToken() {
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
		std::cerr << "Error: failed to generate token\n";
		return (false);
	}
	token_.erase(0, 1);
	token_.erase(token_.size() - 1, 1);
	return (true);
}

bool Api::request(const std::string &login) {
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
	mess_ = findStr("\"location\":");
	if (mess_.empty() || mess_ == "null") {
		std::cerr << "Error: location not found\n";
		return (false);
	}
	mess_.erase(0, 1);
	mess_.erase(mess_.size() - 1, 1);
	return (true);
}

std::string Api::findStr(const std::string &strToFind) {
	std::string str;
	std::ifstream infile_;

	infile_.open("res.txt");
	if (!infile_.is_open()) {
		std::cout << "Error: could not open file 'res.txt'" << std::endl;
		return ("");
	}
	getline(infile_, str, '\0');
	if (infile_.fail() || infile_.bad()) {
		std::cerr << "Error reading" << std::endl;
		return ("");
	}

	size_t start = str.find(strToFind);
	if (start == std::string::npos) {
		std::cerr << "Error: could not find data\n";
		return ("");
	}
	start += strToFind.length();

	size_t end = str.find(",", start);
	if (end == std::string::npos) {
		std::cerr << "Error: could not find data\n";
		return ("");
	}

	return (str.substr(start, end - start));
}

bool Api::executeCmd(std::vector< std::string > &cmd) {
	int child;

	child = fork();
	if (child == -1) {
		std::cerr << "Error: failed to created child process\n";
		return (false);
	}
	if (child == 0) {
		if (!openFile())
			exit(errno);
		if (!findCurlPath()) {
			std::cerr << "Error: could not find path\n";
			exit(errno);
		}
		fillCmd(cmd); //TODO: protect
		if (dup2(resFd_, 1) == -1) {
			std::cerr << "Error: redirection failed\n";
			exit(errno);
		}
		if (execve(curlPath_.c_str(), cmd_, envp_) == -1)
			std::cerr << "Error: execve failed\n";
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
		std::cerr << "Error: could not open res.txt\n";
		return (false);
	}
	return (true);
}

bool Api::findCurlPath() {
	std::string pathVar = getEnvVar("PATH=");
	if (pathVar.empty())
		return (false);

	size_t pos = 0;
	std::string path;
	for (size_t i = 0; i < pathVar.size(); i++) {
		pos = pathVar.find(":");
		if (pos == std::string::npos)
			pos = pathVar.size();
		path.assign(pathVar, 0, pos);
		path += "/curl";
		if (access(path.c_str(), X_OK) == 0) {
			curlPath_ = path.c_str();
			return (true);
		}
		pathVar.erase(0, i + 1);
		path.clear();
	}
	return (false);
}

void Api::fillCmd(std::vector< std::string > &cmd) {
	cmd_ = new char *[cmd.size() + 1];
	for (size_t i = 0; i < cmd.size(); ++i) {
		cmd_[i] = strdup(cmd[i].c_str());
	}
	cmd_[cmd.size()] = NULL;
}

bool Api::curlStatus(int status) {
	if (WIFEXITED(status)) {
		int exitCode = WEXITSTATUS(status);
		if (exitCode != 0) {
			std::cerr << "Curl command failed with exit code: " << exitCode
					  << std::endl;
			return (false);
		}
	} else if (WIFSIGNALED(status)) {
		int signal = WTERMSIG(status);
		std::cerr << "Curl process terminated by signal: " << signal
				  << std::endl;
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

const std::string &Api::getMess(void) const {
	return (mess_);
}

/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */

/*
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* output) {
    size_t totalSize = size * nmemb;
    ((std::string*)output)->append((char*)contents, totalSize);
    return totalSize;
}
*/

/*
	CURL *curl = curl_easy_init();
	if (!curl) {
		std::cerr << "init failed\n";
		return;
	}

    curl_easy_setopt(curl, CURLOPT_URL, "https://api.intra.42.fr/oauth/token");
    curl_easy_setopt(curl, CURLOPT_POST, 1L);

	const std::string &client_id = "";
	const std::string &client_secret =
		"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";
    const std::string &grant_type = "client_credentials";
	std::string post_fields = "grant_type=" + grant_type + "&client_id=" + client_id + "&client_secret=" + client_secret;
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields.c_str());

    std::string response_data;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

    // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

	CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        return;
    }

    std::cout << "response: " << response_data << std::endl;
	curl_easy_cleanup(curl);
	*/