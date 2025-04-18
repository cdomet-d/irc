#ifndef BOT_HPP
#define BOT_HPP

#include "Message.hpp"
#include <arpa/inet.h>
#include <fstream>
#include <netinet/in.h>
#include <string>

class Bot {
  public:
	/*                               ORTHODOX CLASS                           */
	~Bot(void);

	/*                               METHODS                                  */
	static Bot &getInstance(int port, const std::string &pw,
							const std::string &servIp);
	bool createChan();
	bool executeCmd();
	bool registration();
	bool registrationSequence();
	bool requestConnection();
	ssize_t receive();

	/*                               GETTERS                                  */
	int getFd() const;
	bool getSignal() const;
	const stringVec &getMembers() const;

	/*                               SETTERS                                  */
	void setSignal(const bool signum);
	void addClient(const std::string &nick);

	/*                               MEMBERS                                  */
	std::ofstream log_;

  private:
	/*                               MEMBERS                                  */

	param e_param;
	Msg msg;
	stringVec chanMembers;

	int port_;
	int sockFd;
	bool gSign;
	std::string pw_;
	struct sockaddr_in serv_;

	/*                               ORTHODOX CLASS                           */
	Bot(void);
	Bot(int port, std::string pw, std::string servIp);
	Bot(const Bot &rhs);
	Bot &operator=(const Bot &rhs);
};

#endif
