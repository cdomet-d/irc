//HEADER

#ifndef COMMANDPARAM_HPP
#define COMMANDPARAM_HPP

#include <iostream>
#include <vector>

class CommandParam {
  private:
	std::vector< std::string > param_;
	std::vector< void (*)(std::string &) > checkers_;

  public:
	//constructors & destructor
	CommandParam(void);
	CommandParam(std::vector< std::string > param,
				 std::vector< void (*)(std::string &) > checkers);
	CommandParam(const CommandParam &rhs);
	~CommandParam(void);

	//operators
	CommandParam &operator=(const CommandParam &rhs);
	std::string &operator[](unsigned int i);

	//methods
	std::vector< std::string > &getParam(void) {
		return (param_);
	}
	size_t getParamSize(void) {
		return (param_.size());
	}
	void (*getChecker(unsigned int i))(std::string &) {
		return (checkers_[i]);
	}
	size_t getCheckerSize(void) {
		return (checkers_.size());
	}
	//nested class
	class ParamBuilder {
	  private:
		std::vector< std::string > param;
		std::vector< void (*)(std::string &) > checkers;

	  public:
		//constructors & destructor
		ParamBuilder(void);
		ParamBuilder(const ParamBuilder &rhs);
		~ParamBuilder(void);

		//operators
		ParamBuilder &operator=(const ParamBuilder &rhs);

		//methods
		ParamBuilder &addChecker(void (*ft)(std::string &));
		CommandParam *build();
	};
};

void validChan(std::string &param);
void validKey(std::string &param);
void joinChanRequest(std::string &param);
#endif
