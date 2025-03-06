//HEADER

#include "CommandSpec.hpp"

/* constructors & destructor */
CommandSpec::CommandSpec(void) {
	//std::cout << "CommandSpec default constructor called" << std::endl;
}

CommandSpec::CommandSpec(
	std::string name,
	void (*inputTokenizer)(std::string &buffer, CommandParam &param),
	int registrationStage, std::vector< CommandParam * > params, int minParam,
	std::vector< void (*)() > issuerChecks, Executor *cmExecutor) {
	name_ = name;
	inputTokenizer_ = inputTokenizer;
	registrationStage_ = registrationStage;
	params_ = params;
	minParam_ = minParam;
	issuerChecks_ = issuerChecks;
	cmExecutor_ = cmExecutor;
}

CommandSpec::CommandSpec(const CommandSpec &rhs) {
	//std::cout << "CommandSpec copy constructor called" << std::endl;
	*this = rhs;
}

CommandSpec::~CommandSpec(void) {
	//std::cout << "CommandSpec destructor called" << std::endl;
}

/*operators*/
CommandSpec &CommandSpec::operator=(const CommandSpec &rhs) {
	//std::cout << "CommandSpec copy assignment operator called" << std::endl;
	if (this != &rhs) {
		//
	}
	return (*this);
}

/*methods*/
CommandSpec &CommandSpec::process(std::string &buffer, Client &client) {
	(void)client;
	// std::cout << name << std::endl;
	// std::cout << "'" << buffer << "'" << std::endl;
	// std::cout << params.getParams().size() << std::endl;
	void (*tokenizer)(std::string &buffer, CommandParam &param) =
		inputTokenizer_;

	for (size_t i = 0; i < params_.size(); i++)
		tokenizer(buffer, *params_[i]);
	for (size_t i = 0; i < params_.size(); i++) {
		for (size_t j = 0; j < params_[i]->getCheckerSize(); j++) {
			void (*checker)(std::string &) = (*params_[i]).getChecker(j);
			for (size_t n = 0; n < params_[i]->getParamSize(); n++)
				checker((*params_[i])[n]);
		}
	}
	// for (size_t i = 0; i < params_.size(); i++)
	// {
	// 	std::cout << "\nparam[" << i << "] : " << std::endl;
	// 	for (size_t j = 0; j < (*params_[i]).getParamSize(); j++)
	// 		std::cout << (*params_[i])[j] << std::endl;
	// }

	return (*this);
}

std::string CommandSpec::getName(void) {
	return (name_);
}

/*----------------------------------- nested class -----------------------------------*/
/* constructors & destructor */
CommandSpec::CommandBuilder::CommandBuilder(void) {
	//std::cout << "CommandBuilder default constructor called" << std::endl;
}

CommandSpec::CommandBuilder::CommandBuilder(const CommandBuilder &rhs) {
	//std::cout << "CommandBuilder copy constructor called" << std::endl;
	*this = rhs;
}

CommandSpec::CommandBuilder::~CommandBuilder(void) {
	//std::cout << "CommandBuilder destructor called" << std::endl;
}

/*operators*/
CommandSpec::CommandBuilder &
CommandSpec::CommandBuilder::operator=(const CommandBuilder &rhs) {
	//std::cout << "CommandBuilder copy assignment operator called" << std::endl;
	if (this != &rhs) {
		//
	}
	return (*this);
}

/*methods*/
CommandSpec::CommandBuilder &
CommandSpec::CommandBuilder::Name(const std::string &name) {
	// name = name;
	(void)name;
	return (*this);
}

CommandSpec::CommandBuilder &CommandSpec::CommandBuilder::InputTokenizer(
	void (*ft)(std::string &buffer, CommandParam &param)) {
	inputTokenizer_ = ft;
	return (*this);
}

CommandSpec::CommandBuilder &
CommandSpec::CommandBuilder::Registration(int stage) {
	registrationStage_ = stage;
	return (*this);
}

CommandSpec::CommandBuilder &
CommandSpec::CommandBuilder::Parameters(CommandParam *param) {
	params_.push_back(param);
	return (*this);
}

CommandSpec::CommandBuilder &
CommandSpec::CommandBuilder::MinParam(int minParam) {
	minParam_ = minParam;
	return (*this);
}

CommandSpec::CommandBuilder &
CommandSpec::CommandBuilder::IssuerChecks(void (*ft)()) {
	issuerChecks_.push_back(ft);
	return (*this);
}

CommandSpec::CommandBuilder &
CommandSpec::CommandBuilder::CmExecutor(Executor *cmExecutor) {
	cmExecutor_ = cmExecutor;
	return (*this);
}

CommandSpec *CommandSpec::CommandBuilder::build() {
	return (new CommandSpec(name_, inputTokenizer_, registrationStage_, params_,
							minParam_, issuerChecks_, cmExecutor_));
}
