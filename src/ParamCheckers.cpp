//HEADER
#include "CommandParam.hpp"

void	validChan(std::string& param)
{
	if (param[0] != '#')
		std::cerr << param << " :No such channel" << std::endl;
}

void	validKey(std::string& param)
{

}

void	joinChanRequest(std::string& param)
{
	
}