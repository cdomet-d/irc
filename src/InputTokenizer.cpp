//HEADER
#include "CommandParam.hpp"

void	splitOnComa(std::string& buffer, CommandParam& param)
{
	size_t i = 0;
	size_t	index = 0;

	while (i < buffer.size() && buffer[i] != ' ')
	{
		index = buffer.find_first_of(", ", 0);
		if (index == std::string::npos)
			index = buffer.size();
		param.getParam().push_back(buffer.substr(0, index));
		if (buffer[index] != ' ')
			index++;
		buffer.erase(0, index);
	}
	if (buffer[i] == ' ')
		while (i < buffer.size() && buffer[i] == ' ')
			buffer.erase(0, 1);
}