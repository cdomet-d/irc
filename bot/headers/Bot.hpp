#ifndef BOT_HPP
#define BOT_HPP

#include <string>

class Bot {
  public:
	/*                               ORTHODOX CLASS                           */
	~Bot(void) {}

	/*                               METHODS                                  */
	static Bot &getInstance(int port, const std::string &pw);
	/*                               GETTERS                                  */

	/*                               SETTERS                                  */
  private:
	/*                               MEMBERS                                  */
	int port_;
	std::string pw_;
	
	/*                               ORTHODOX CLASS                           */
	Bot(void);
	Bot(int port, std::string pw);
	Bot(const Bot &rhs);
	Bot &operator=(const Bot &rhs);
};

#endif
