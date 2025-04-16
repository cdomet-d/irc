//HEADER

#ifndef API_HPP
#define API_HPP

#include <iostream>
#include <curl/curl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

class Api {
  public:
	/*                               ORTHODOX CLASS                           */
    Api(void);
    Api(const Api &rhs);
	Api &operator=(const Api &rhs);
	~Api(void);

	/*                               METHODS                                  */
    void apiRequest(const std::string &login);
	
	/*                               GETTERS                                  */
	void getToken(void);
	/*                               SETTERS                                  */
    private:
	/*                               MEMBERS                                  */
	std::string token;
};

#endif
