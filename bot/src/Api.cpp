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

Api::Api(void) : cmd_(NULL), envp_(NULL) {}

Api::Api(char **envp) : cmd_(NULL), envp_(envp) {

}

Api::Api(const Api &rhs) {
	*this = rhs;
}

Api::~Api(void) {
	// for (size_t i = 0; cmd_[i]; i++)
	// 	free(cmd_[i]);
	// free(cmd_);
}

Api &Api::operator=(const Api &rhs) {
	// rhs instructions
	(void)rhs;
	return *this;
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */

bool Api::findSecret() {
	secret_ = getEnvVar("IRCBOT_SECRET=");
	if (secret_.empty())
		return (false);
	return (true);
}

bool Api::request(const std::string &login) {
	(void)login;

	return (true);
}
//curl -H "Authorization: Bearer 7e507486b4010cca392f6396ed53f36bc888084a6955ad962a56dbab88e8993f" https://api.intra.42.fr/v2/cursus/42/users | jq

bool Api::generateToken() {
	//TODO: a token lasts 2 hours
	clientIUD_ = "u-s4t2ud-ad20c0580b5b2d1e67736549dd536f87146a2340a5cbd41aba0c1da8655e0293";
	std::vector<std::string> cmd;
	cmd.push_back("curl");
	cmd.push_back("-s");
	cmd.push_back("-X");
	cmd.push_back("POST");
	cmd.push_back("--data");
	cmd.push_back("grant_type=client_credentials&client_id=" + clientIUD_ +
				"&client_secret=" + secret_);
	cmd.push_back("https://api.intra.42.fr/oauth/token");

	cmd_ = new char*[cmd.size() + 1];
	for (size_t i = 0; i < cmd.size(); ++i) {
		cmd_[i] = strdup(cmd[i].c_str());
	}
	cmd_[cmd.size()] = NULL;
	
	executeCmd();
	std::ifstream	infile;
	std::string		str;
	infile.open("res.txt");
	if (!infile.is_open())
	{
		std::cout << "Error: could not open file 'data.csv'" << std::endl;
		return (false);
	}
	getline(infile, str, '\0');
	if (infile.fail() || infile.bad())
	{
		std::cerr << "Error reading" << std::endl;
		return (false);
	}

	std::string key = "\"access_token\":\"";
	size_t start = str.find(key);
	if (start == std::string::npos){
		std::cerr << "Error: no token\n";
		return (false);
	}
	start += key.length();

	size_t end = str.find("\"", start);
	if (end == std::string::npos) {
		std::cerr << "Error: no token\n";
		return (false);
	}
	
	token_ = str.substr(start, end - start);
	std::cout << "token: " << token_ << std::endl;

	return (true);
}

bool Api::executeCmd() {
	int child;

	resFd_ = open("res.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (resFd_ == -1) {
		std::cerr << "Error: could not open res.txt\n";
		return (false);
	}
	if (!findCurlPath()) {
		std::cerr << "Error: could not find path\n";
		return (false);
	}
	child = fork();
	if (child == -1) {
		std::cerr << "Error: failed to created child process\n";
		return (false);
	}
	if (child == 0) {
		if (dup2(resFd_, 1) == -1) {
			std::cerr << "Error: redirection failed\n";
			exit(EXIT_FAILURE);
		}
		if (execve(curlPath_.c_str(), cmd_, envp_) == -1)
			std::cerr << "Error: execve failed\n";
		close(0);
		close(1);
		close(resFd_);
		exit(errno);
	}
	close(resFd_);
	int status;
	waitpid(child, &status, 0);
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