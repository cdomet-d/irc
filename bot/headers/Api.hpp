//HEADER

#ifndef API_HPP
#define API_HPP

#include <iostream>
#include <sstream>
#include <cstring>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>
# include <vector>
# include <fstream>


class Api {
  public:
	/*                               ORTHODOX CLASS                           */
    Api(char **envp);
    Api(const Api &rhs);
	Api &operator=(const Api &rhs);
	~Api(void);
	
	/*                               METHODS                                  */
    bool request(const std::string &login);
	bool findSecret();
	bool generateToken();
	bool executeCmd(std::vector< std::string> &cmd);
	bool findCurlPath();
	bool openFile();
	std::string findStr(const std::string &strToFind);
	void fillCmd(std::vector< std::string> &cmd);

	/*                               GETTERS                                  */
	std::string getEnvVar(const std::string &varName);
	const std::string &getMess(void) const;

	/*                               SETTERS                                  */
    
	private:
	/*                               MEMBERS                                  */
	std::string token_;
	std::string secret_;
	std::string clientIUD_;
	std::string curlPath_;
	char **cmd_;
	char **envp_;
	int resFd_;
	std::string mess_;

    Api(void);
};

#endif
