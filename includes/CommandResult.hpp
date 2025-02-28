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
		// CommandResult&	process(std::string& buffer);

		//getters
		std::string		getName(void);
		
		//setters
		// std::string		setName(void);

		// //nested class
		// class	test
		// {
		// 	private:
		// 		//attributes
		// 		CommandResult&	cm;
		// 	public:
		// 		//constructors & destructor
		// 		test(void);
		// 		test(const test& obj);
		// 		~test(void);
		
		// 		//operators
		// 		test&	operator=(const test& obj);
		// };
};

#endif



