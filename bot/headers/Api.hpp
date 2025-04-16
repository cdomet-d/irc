//HEADER

#ifndef API_HPP
#define API_HPP

#include <iostream>
#include <unistd.h>
#include <cstring>
# include <fcntl.h>


class Api {
  public:
	/*                               ORTHODOX CLASS                           */
    Api(void);
    Api(char **envp);
    Api(const Api &rhs);
	Api &operator=(const Api &rhs);
	~Api(void);

	/*                               METHODS                                  */
    bool request(const std::string &login);
	bool findSecret();
	bool generateToken();
	bool executeCmd();
	/*                               GETTERS                                  */
	// void getToken(void);
	/*                               SETTERS                                  */
    private:
	/*                               MEMBERS                                  */
	std::string token_;
	std::string secret_;
	char *curlPath_;
	char **cmd_;
	char **envp_;
	int resFd;
};

#endif
