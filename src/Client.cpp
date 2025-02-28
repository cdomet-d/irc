//HEADER

#include "Client.hpp"

/* constructors & destructor */
Client::Client(void)
{
	//std::cout << "Client default constructor called" << std::endl;
}

Client::Client(const Client& obj)
{
	//std::cout << "Client copy constructor called" << std::endl;
	*this = obj;
}

Client::~Client(void)
{
	//std::cout << "Client destructor called" << std::endl;
}

/*operators*/
Client&	Client::operator=(const Client& obj)
{
	//std::cout << "Client copy assignment operator called" << std::endl;
	if (this != &obj)
	{
		this->registration = obj.registration;
	}
	return (*this);
}
