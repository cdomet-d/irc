//HEADER

#ifndef COMMANDPARAM_HPP
# define COMMANDPARAM_HPP

# include <iostream>
# include <vector>

class	CommandParam
{
	private:
		std::vector<std::string>	param;
		std::vector<void(*)()>		checkers;
	public:
		//constructors & destructor
		CommandParam(void);
		CommandParam(const CommandParam& obj);
		~CommandParam(void);

		//operators
		CommandParam&	operator=(const CommandParam& obj);

		//methods
		CommandParam&	addChecker(void(*ft)());
		std::vector<std::string>&	getParam(void)
		{
			return (this->param);
		}
};

void	validChan();
void	validKey();
void	joinChanRequest();
#endif
