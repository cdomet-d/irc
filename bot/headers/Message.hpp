#ifndef Msg_HPP
#define Msg_HPP

#include <string>
#include <vector>

typedef std::vector< std::string > stringVec;

class Msg {
  public:
	/*                               ORTHODOX CLASS                           */
	Msg(void);
	Msg(const Msg &rhs);
	~Msg(void);
	Msg &operator=(const Msg &rhs);

	/*                               METHODS                                  */
	bool processBuf();
	std::string::size_type Msg::evalTerm() const;
	stringVec vectorSplit(std::string &s, char del);
	void clear();
	void removeNl();
	void trimConsecutiveSpaces();


	/*                               GETTERS                                  */

	/*                               SETTERS                                  */
	void setRcv(const std::string &rcv);

  private:
	std::string rcv_;
};

#endif