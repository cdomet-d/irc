//HEADER

#ifndef COMMANDSPEC_HPP
#define COMMANDSPEC_HPP

#include "Client.hpp"
#include "CommandParam.hpp"
#include "Executor.hpp"
#include "Join.hpp"
#include <iostream>

class CommandSpec {
  private:
	Executor *cmExecutor_;
	int minParam_;
	int registrationStage_;
	std::string name_;
	std::vector< CommandParam * > params_;
	std::vector< void (*)() > issuerChecks_;
	void (*inputTokenizer_)(std::string &buffer, CommandParam &param);

  public:
	//constructors & destructor
	CommandSpec(void);
	CommandSpec(std::string name,
				void (*inputTokenizer)(std::string &buffer,
									   CommandParam &param),
				int registrationStage, std::vector< CommandParam * > params,
				int minParam, std::vector< void (*)() > issuerChecks,
				Executor *cmExecutor);
	CommandSpec(const CommandSpec &rhs);
	~CommandSpec(void);

	//operators
	CommandSpec &operator=(const CommandSpec &rhs);

	//method
	CommandSpec &process(std::string &buffer, Client &client);

	//getters
	std::string getName(void);

	// nested class
	class CommandBuilder //builds a command
	{
	  private:
		Executor *cmExecutor_;
		int minParam_;
		int registrationStage_;
		std::string name_;
		std::vector< CommandParam * > params_;
		std::vector< void (*)() > issuerChecks_;
		void (*inputTokenizer_)(std::string &buffer, CommandParam &param);

	  public:
		//constructors & destructor
		CommandBuilder(void);
		CommandBuilder(const CommandBuilder &rhs);
		~CommandBuilder(void);

		//operators
		CommandBuilder &operator=(const CommandBuilder &rhs);

		//methods
		CommandBuilder &Name(const std::string &name);
		CommandBuilder &Registration(int stage);
		CommandBuilder &IssuerChecks(void (*ft)());
		CommandBuilder &InputTokenizer(void (*ft)(std::string &buffer,
												  CommandParam &param));
		CommandBuilder &Parameters(CommandParam *param);
		CommandBuilder &MinParam(int minParam);
		CommandBuilder &CmExecutor(Executor *cmExecutor);
		CommandSpec *build();
	};
};

void splitOnComa(std::string &buffer, CommandParam &param);

#endif
