#ifndef BOT_HPP
#define BOT_HPP

#include "Message.hpp"
#include <arpa/inet.h>
#include <fstream>
#include <netinet/in.h>
#include <string>
#include "Api.hpp"

class Bot {
  public:
	/*                               ORTHODOX CLASS                           */
	~Bot(void);

	/*                               METHODS                                  */
	static Bot &getInstance(int port, const std::string &pw,
							const std::string &servIp, char *envp[]);
	bool createChan();
	bool executeCmd();
	bool findLoginPos(const std::string &login);
	bool registration();
	bool registrationSequence();
	bool requestConnection();
	bool run();
	ssize_t receive();

	/*                               GETTERS                                  */
	int getFd() const;
	bool getSignal() const;

	/*                               SETTERS                                  */
	void setSignal(const bool signum);

	/*                               MEMBERS                                  */
	std::ofstream log_;

  private:
	enum param {
		prefix_,
		cmd_,
		target_,
		msg_
	} e_param;
	/*                               MEMBERS                                  */
	Msg msg;
	Api api;

	int port_;
	int sockFd;
	bool gSign;
	std::string pw_;
	struct sockaddr_in serv_;

	/*                               ORTHODOX CLASS                           */
	Bot(void);
	Bot(int port, std::string pw, std::string servIp, char *envp[]);
	Bot(const Bot &rhs);
	Bot &operator=(const Bot &rhs);
};

#endif
