//HEADER

#ifndef COMMANDRESULT_HPP
# define COMMANDRESULT_HPP

# include <iostream>

class	CommandResult
{
	private:
		std::string	name;
	public:
		//constructors & destructor
		CommandResult(void);
		CommandResult(const CommandResult& obj);
		~CommandResult(void);

		//operators
		CommandResult&	operator=(const CommandResult& obj);
		
		//method
		CommandResult&	process(std::string& buffer);
		std::string		getName(void);
		
};

#endif



