//HEADER

#ifndef DIRECTOR_HPP
# define DIRECTOR_HPP

# include <map>
# include <iostream>
# include "CmBuilder.hpp"

class Director
{
public:
	/*                               ORTHODOX CLASS                           */
	Director(void);
	Director(const Director &rhs);
	~Director(void);
	Director &operator=(const Director &rhs);

	/*                               METHODS                                  */
	void	buildCommands();

private:
	std::map<std::string, CmBuilder>	cmds;
};

#endif
