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

Api::Api(void) : curlPath_(NULL), cmd_(NULL), envp_(NULL) {}

Api::Api(char **envp) : curlPath_(NULL), cmd_(NULL), envp_(envp) {}

Api::Api(const Api &rhs) {
	*this = rhs;
}

Api::~Api(void) {
	close(resFd);
}

Api &Api::operator=(const Api &rhs) {
	// rhs instructions
	(void)rhs;
	return *this;
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */
bool Api::request(const std::string &login) {
	(void)login;

	return (true);
}
// curl -X POST --data "grant_type=client_credentials&client_id=u-s4t2ud-ad20c0580b5b2d1e67736549dd536f87146a2340a5cbd41aba0c1da8655e0293&client_secret=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" https://api.intra.42.fr/oauth/token | jq
//curl -H "Authorization: Bearer 7e507486b4010cca392f6396ed53f36bc888084a6955ad962a56dbab88e8993f" https://api.intra.42.fr/v2/cursus/42/users | jq

bool Api::findSecret() {
	for (size_t i = 0; i < std::strlen(*envp_); i++) {
		if (!std::strncmp(envp_[i], "IRCBOT_SECRET=", 15)) {
			secret_ = envp_[i] + 15;
			return (true);
		}
	}
	return (false);
}

/*
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* output) {
    size_t totalSize = size * nmemb;
    ((std::string*)output)->append((char*)contents, totalSize);
    return totalSize;
}
*/

bool Api::generateToken() {
	//TODO: a token lasts 2 hours

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
}

bool Api::executeCmd() {
	int child;

	resFd = open("res.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (resFd) {
		std::cerr << "Error: could not open res.txt\n";
		return (false);
	}
	child = fork();
	if (child == -1) {
		std::cerr << "Error: failed to created child process\n";
		return (false);
	}
	if (child == 0) {
		if (dup2(resFd, 1) == -1) {
			std::cerr << "Error: redirection failed\n";
			exit(EXIT_FAILURE);
		}
		if (execve(curlPath_, cmd_, envp_) == -1) {
            close(0);
            close(1);
            std::cerr << "Error: execve failed\n";
            exit(errno);
        }
	}
}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */
/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */
