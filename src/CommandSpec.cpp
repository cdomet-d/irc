//HEADER

#include "CommandSpec.hpp"

/* constructors & destructor */
CommandSpec::CommandSpec(void)
{
	//std::cout << "CommandSpec default constructor called" << std::endl;
}

CommandSpec::CommandSpec(const CommandSpec& obj)
{
	//std::cout << "CommandSpec copy constructor called" << std::endl;
}

CommandSpec::~CommandSpec(void)
{
	//std::cout << "CommandSpec destructor called" << std::endl;
}

/*operators*/
CommandSpec&	CommandSpec::operator=(const CommandSpec& obj)
{
	//std::cout << "CommandSpec copy assignment operator called" << std::endl;
	return (*this);
}

/*methods*/
CommandSpec&	CommandSpec::Name(const std::string& name)
{
	this->name = name;
	return (*this);
}

CommandSpec&	CommandSpec::InputTokenizer(void(*ft)())
{
	this->inputTokenizer = ft;
	return (*this);
}

CommandSpec&	CommandSpec::Registration(int stage)
{
	this->registrationStage = stage;
	return (*this);
}

CommandSpec&	CommandSpec::build()
{
	return (*this);
}

CommandResult&	CommandSpec::getCmdResult()
{
	return (this->cmd);
}