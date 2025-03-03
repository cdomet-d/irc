//HEADER

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>

class	Client
{
	private:
		//attributes
		int	registration;
	public:
		//constructors & destructor
		Client(void);
		Client(const Client& obj);
		~Client(void);

		//operators
		Client&	operator=(const Client& obj);
};

#endif
