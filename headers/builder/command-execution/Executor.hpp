//HEADER

#ifndef EXECUTOR_HPP
# define EXECUTOR_HPP

# include <iostream>

class	Executor
{
	private:
		//attributes
	public:
		//constructors & destructor
		Executor(void) {};
		virtual ~Executor(void) {};

		//methods
		virtual void	execute() = 0;
};

#endif
