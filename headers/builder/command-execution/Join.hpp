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
		Join(const Join& rhs);
		~Join(void);

		//operators
		Join&	operator=(const Join& rhs);

		//method
		void	execute();
};

#endif
