//HEADER

#ifndef API_HPP
#define API_HPP

#include <cstring>
#include <ctime>
#include <errno.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
#include "Reply.hpp"

class Api {
  public:
	/*                               ORTHODOX CLASS                           */
	Api(void);
	Api(char **envp);
	Api(const Api &rhs);
	Api &operator=(const Api &rhs);
	~Api(void);

	/*                               METHODS                                  */
	bool curlStatus(int status);
	bool executeCmd(std::vector< std::string > &cmd);
	bool findCurlPath();
	bool findSecret();
	bool openFile();
	bool requestLocation(const std::string &login);
	bool requestToken();
	std::string findStr(const std::string &strToFind);
	void fillCmd(std::vector< std::string > &cmd);

	/*                               GETTERS                                  */
	std::string getEnvVar(const std::string &varName);
	const std::string &getPos(void) const;

	/*                               SETTERS                                  */

  private:
	/*                               MEMBERS                                  */
	char **cmd_;
	char **envp_;
	int resFd_;
	std::string clientIUD_;
	std::string curlPath_;
	std::string pos_;
	std::string secret_;
	std::string token_;
	std::time_t time_;
	std::string URL_;
};

#endif
