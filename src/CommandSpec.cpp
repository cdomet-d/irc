//HEADER

#include "CommandSpec.hpp"

/* constructors & destructor */
CommandSpec::CommandSpec(void)
{
	//std::cout << "CommandSpec default constructor called" << std::endl;
}

CommandSpec::~CommandSpec(void)
{
	//std::cout << "CommandSpec destructor called" << std::endl;
}

/*methods*/
CommandSpec&	CommandSpec::Name(const std::string& name)
{
	this->name = name;
	return (*this);
}

CommandSpec&	CommandSpec::InputTokenizer(void(*ft)(std::string& buffer, CommandParam& param))
{
	this->inputTokenizer = ft;
	return (*this);
}

CommandSpec&	CommandSpec::Registration(int stage)
{
	this->registrationStage = stage;
	return (*this);
}

CommandSpec&	CommandSpec::Parameters(ParamGenerator& params)
{
	this->params = params;
	return (*this);
}

CommandSpec&	CommandSpec::MinParam(int minParam)
{
	this->minParam = minParam;
	return (*this);
}

CommandSpec&	CommandSpec::IssuerChecks(void(*ft)())
{
	this->issuerChecks.push_back(ft);
	return (*this);
}

CommandSpec&	CommandSpec::CmExecutor(Executor* cmExecutor)
{
	this->cmExecutor = cmExecutor;
	return (*this);
}

CommandSpec&	CommandSpec::build()
{
	return (*this);
}

// CommandResult&	CommandSpec::getCmdResult()
// {
// 	return (this->cmd);
// }

std::string&	CommandSpec::getName(void)
{
	return (this->name);
}

CommandSpec&	CommandSpec::process(std::string& buffer, Client& client)
{
	// std::cout << this->name << std::endl;
	// std::cout << "'" << buffer << "'" << std::endl;
	// std::cout << params.getParams().size() << std::endl;
	void(*tokenizer)(std::string& buffer, CommandParam& param)	= this->getInputTokenizer();
	
	for (size_t i = 0; i < params.getParams().size(); i++)
		tokenizer(buffer, params[i]);

	// for (size_t i = 0; i < params.getParams().size(); i++)
	// {
	// 	std::cout << "\nparam[" << i << "] : " << std::endl;
	// 	for (size_t j = 0; j < params[i].getParam().size(); j++)
	// 		std::cout << params[i].getParam()[j] << std::endl;
	// }

	return (*this);
}