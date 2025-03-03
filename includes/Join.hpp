//HEADER

#ifndef JOIN_HPP
# define JOIN_HPP

# include <iostream>
# include "Executor.hpp"

class	Join : public Executor
{
	private:
		//attributes
	public:
		//constructors & destructor
		Join(void);
		Join(const Join& obj);
		~Join(void);

		//operators
		Join&	operator=(const Join& obj);

		//method
		void	execute();
};

#endif
