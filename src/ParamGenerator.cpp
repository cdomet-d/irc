//HEADER

#include "ParamGenerator.hpp"

/* constructors & destructor */
ParamGenerator::ParamGenerator(void)
{
	//std::cout << "ParamGenerator default constructor called" << std::endl;
}

ParamGenerator::ParamGenerator(const ParamGenerator& obj)
{
	//std::cout << "ParamGenerator copy constructor called" << std::endl;
}

ParamGenerator::~ParamGenerator(void)
{
	//std::cout << "ParamGenerator destructor called" << std::endl;
}

/*operators*/
ParamGenerator&	ParamGenerator::operator=(const ParamGenerator& obj)
{
	//std::cout << "ParamGenerator copy assignment operator called" << std::endl;
	return (*this);
}
