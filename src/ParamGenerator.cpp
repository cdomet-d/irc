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

/*methods*/
ParamGenerator&	ParamGenerator::addParam(CommandParam& param)
{
	this->params.push_back(param);
	return (*this);
}

ParamGenerator&	ParamGenerator::addOptParam(CommandParam& paramOpt)
{
	this->paramsOpt.push_back(paramOpt);
	return (*this);
}
