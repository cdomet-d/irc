//HEADER

#ifndef API_HPP
#define API_HPP

#include <iostream>
#include <curl/curl.h>

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

	/*                               SETTERS                                  */
    private:
	/*                               MEMBERS                                  */
	
};

#endif
