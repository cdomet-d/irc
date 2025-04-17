#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <unistd.h>
#include <vector>

typedef std::vector< std::string > stringVec;

class Msg {
  public:
	/*                               ORTHODOX CLASS                           */
	Msg(void);
	~Msg(void);

	/*                               METHODS                                  */
	bool processBuf();
	std::string::size_type evalTerm() const;
	stringVec vectorSplit(char del);
	void clear();
	void removeNl();
	bool rplIs(const std::string &expected) const;
	void trimConsecutiveSpaces();
	ssize_t _recv(const int fd);
	void clearCmdParam();

	/*                               GETTERS                                  */
	const std::string &getRcv() const;

	/*                               SETTERS                                  */
	void setRcv();

	stringVec cmdParam_;

  private:
	Msg(const Msg &rhs);
	Msg &operator=(const Msg &rhs);
	std::string rcv_;
	char rcvbuf[1024];
};

#endif