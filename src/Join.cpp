//HEADER

#include "Join.hpp"

/* constructors & destructor */
Join::Join(void)
{
	//std::cout << "Join default constructor called" << std::endl;
}

Join::Join(const Join& obj)
{
	//std::cout << "Join copy constructor called" << std::endl;
	*this = obj;
}

Join::~Join(void)
{
	//std::cout << "Join destructor called" << std::endl;
}

/*operators*/
Join&	Join::operator=(const Join& obj)
{
	//std::cout << "Join copy assignment operator called" << std::endl;
	if (this != &obj)
	{
	}
	return (*this);
}

void	Join::execute()
{

}