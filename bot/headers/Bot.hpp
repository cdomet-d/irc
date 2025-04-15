#ifndef BOT_HPP
#define BOT_HPP

#include <arpa/inet.h>
#include <fstream>
#include <netinet/in.h>
#include <string>
#include <sys/types.h>

class Bot {
  public:
	/*                               ORTHODOX CLASS                           */
	~Bot(void);

	/*                               METHODS                                  */
	static Bot &getInstance(int port, const std::string &pw,
							const std::string &servIp);
	bool requestConnection();
	
	/*                               GETTERS                                  */
	int getFd() const;
	
	/*                               SETTERS                                  */

	/*                               MEMBERS                                  */
	std::ofstream log_;

  private:
	/*                               MEMBERS                                  */
	int port_;
	int sockFd;
	std::string pw_;
	struct sockaddr_in serv_;

	/*                               ORTHODOX CLASS                           */
	Bot(void);
	Bot(int port, std::string pw, std::string servIp);
	Bot(const Bot &rhs);
	Bot &operator=(const Bot &rhs);
};

#endif
