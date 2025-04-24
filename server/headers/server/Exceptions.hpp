#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>

class ObjectNotFound : public std::exception {
  public:
	ObjectNotFound(const char *err);
	const char *what() const throw();

  private:
	const char *errMessage;
};

#endif
