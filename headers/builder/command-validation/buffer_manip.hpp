//HEADER

#ifndef N_FORMATMESS_HPP
#define N_FORMATMESS_HPP

#include "Client.hpp"
#include "typedef.hpp"

namespace buffer_manip {
	bool prepareCommand(Client &sender);
	stringVec vectorSplit(std::string &s, char del);
}; // namespace buffer_manip

#endif
