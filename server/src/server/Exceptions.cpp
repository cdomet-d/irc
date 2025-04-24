#include "Exceptions.hpp"

ObjectNotFound::ObjectNotFound(const char *err) : errMessage(err) {}
const char *ObjectNotFound::what() const throw() {
	return (errMessage);
}