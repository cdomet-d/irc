//HEADER

#include "CommandSpec.hpp"

/* constructors & destructor */
CommandSpec::CommandSpec(void)
{
	//std::cout << "CommandSpec default constructor called" << std::endl;
}

CommandSpec::CommandSpec(std::string name, void(*inputTokenizer)(std::string& buffer, CommandParam& param), int registrationStage, \
					std::vector<CommandParam*> params, int minParam, std::vector<void(*)()>	issuerChecks, Executor* cmExecutor)
{
	this->name = name;
	this->inputTokenizer = inputTokenizer;
	this->registrationStage = registrationStage;
	this->params = params;
	this->minParam = minParam;
	this->issuerChecks = issuerChecks;
	this->cmExecutor = cmExecutor;
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
CommandSpec&	CommandSpec::process(std::string& buffer, Client& client)
{
	// std::cout << this->name << std::endl;
	std::cout << "'" << buffer << "'" << std::endl;
	// std::cout << params.getParams().size() << std::endl;
	void(*tokenizer)(std::string& buffer, CommandParam& param)	= this->inputTokenizer;
	
	for (size_t i = 0; i < params.getParams().size(); i++)
		tokenizer(buffer, params[i]);

	for (size_t i = 0; i < params.getParams().size(); i++)
	{
		std::cout << "\nparam[" << i << "] : " << std::endl;
		for (size_t j = 0; j < params[i].getParam().size(); j++)
			std::cout << params[i].getParam()[j] << std::endl;
	}

	return (*this);
}

std::string		CommandSpec::getName(void)
{
	return (this->name);
}

/*nested class -----------------------------------*/
/* constructors & destructor */
CommandSpec::CommandBuilder::CommandBuilder(void)
{
	//std::cout << "CommandBuilder default constructor called" << std::endl;
}

CommandSpec::CommandBuilder::CommandBuilder(const CommandBuilder& obj)
{
	//std::cout << "CommandBuilder copy constructor called" << std::endl;
}

CommandSpec::CommandBuilder::~CommandBuilder(void)
{
	//std::cout << "CommandBuilder destructor called" << std::endl;
}

/*operators*/
CommandSpec::CommandBuilder&	CommandSpec::CommandBuilder::operator=(const CommandBuilder& obj)
{
	//std::cout << "CommandBuilder copy assignment operator called" << std::endl;
	return (*this);
}

/*methods*/
CommandSpec::CommandBuilder&	CommandSpec::CommandBuilder::Name(const std::string& name)
{
	this->name = name;
	return (*this);
}

CommandSpec::CommandBuilder&	CommandSpec::CommandBuilder::InputTokenizer(void(*ft)(std::string& buffer, CommandParam& param))
{
	this->inputTokenizer = ft;
	return (*this);
}

CommandSpec::CommandBuilder&	CommandSpec::CommandBuilder::Registration(int stage)
{
	this->registrationStage = stage;
	return (*this);
}

CommandSpec::CommandBuilder&	CommandSpec::CommandBuilder::Parameters(CommandParam* param)
{
	this->params.push_back(param);
	return (*this);
}

CommandSpec::CommandBuilder&	CommandSpec::CommandBuilder::MinParam(int minParam)
{
	this->minParam = minParam;
	return (*this);
}

CommandSpec::CommandBuilder&	CommandSpec::CommandBuilder::IssuerChecks(void(*ft)())
{
	this->issuerChecks.push_back(ft);
	return (*this);
}

CommandSpec::CommandBuilder&	CommandSpec::CommandBuilder::CmExecutor(Executor* cmExecutor)
{
	this->cmExecutor = cmExecutor;
	return (*this);
}

CommandSpec*	CommandSpec::CommandBuilder::build()
{
	return (new CommandSpec(name, inputTokenizer, registrationStage, params, minParam, issuerChecks, cmExecutor));
}
