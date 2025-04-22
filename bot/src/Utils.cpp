//HEADER

#include "Utils.hpp"

stringVec vectorSplit(std::string &rcv, char del) {
	stringVec result;
	std::string token;

	std::istringstream stream(rcv);
	while (std::getline(stream, token, del))
		result.push_back(token);
	return (result);
}
