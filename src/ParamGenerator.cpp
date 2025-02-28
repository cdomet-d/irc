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
	*this = obj;
}

ParamGenerator::~ParamGenerator(void)
{
	//std::cout << "ParamGenerator destructor called" << std::endl;
}

/*operators*/
ParamGenerator&	ParamGenerator::operator=(const ParamGenerator& obj)
{
	//std::cout << "ParamGenerator copy assignment operator called" << std::endl;
	if (this != &obj)
	{
		this->params = obj.params;
		this->paramsOpt = obj.paramsOpt;
	}
	return (*this);
}

CommandParam&	ParamGenerator::operator[](unsigned int i)
{
	//security?
	return (this->params[i]);
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

std::vector<CommandParam>&	ParamGenerator::getParams(void)
{
	return (this->params);
}

std::vector<CommandParam>&	ParamGenerator::getOptParams(void)
{
	return (this->paramsOpt);
}
