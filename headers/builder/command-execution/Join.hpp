//HEADER

#ifndef JOIN_HPP
#define JOIN_HPP

#include "Executor.hpp"
#include <iostream>

class Join : public Executor {
  private:
	//attributes
  public:
	//constructors & destructor
	Join(void);
	Join(const Join &rhs);
	~Join(void);

	//operators
	Join &operator=(const Join &rhs);

	//method
	void execute();
};

#endif
