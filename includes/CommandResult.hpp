//HEADER

#ifndef COMMANDRESULT_HPP
# define COMMANDRESULT_HPP

# include <iostream>

class	CommandResult
{
	private:
		//attributes
	public:
		//constructors & destructor
		CommandResult(void);
		CommandResult(const CommandResult& obj);
		~CommandResult(void);

		//operators
		CommandResult&	operator=(const CommandResult& obj);
		
		//method
		CommandResult&	process(std::string& buffer);

		//nested class
		class	CommandSpec //builds a command
		{
			private:
				//attributes
			public:
				//constructors & destructor
				CommandSpec(void);
				CommandSpec(const CommandSpec& obj);
				~CommandSpec(void);

				//operators
				CommandSpec&	operator=(const CommandSpec& obj);

		};
};

#endif



