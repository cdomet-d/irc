//HEADER

#ifndef COMMANDPARAM_HPP
# define COMMANDPARAM_HPP

# include <iostream>
# include <vector>

class	CommandParam
{
	private:
		std::vector<std::string>	param;
		std::vector<void(*)()>		checkers;
	public:
		//constructors & destructor
		CommandParam(void);
		CommandParam(std::vector<std::string> param, std::vector<void(*)()> checkers);
		CommandParam(const CommandParam& obj);
		~CommandParam(void);

		//operators
		CommandParam&	operator=(const CommandParam& obj);
		// CommandParam&		operator[](unsigned int i);

		//methods
		std::vector<std::string>&	getParam(void) {
			return (this->param);}

		//nested class
		class	ParamBuilder
		{
			private:
				std::vector<std::string>	param;
				std::vector<void(*)()>		checkers;
			public:
				//constructors & destructor
				ParamBuilder(void);
				ParamBuilder(const ParamBuilder& obj);
				~ParamBuilder(void);

				//operators
				ParamBuilder&		operator=(const ParamBuilder& obj);

				//methods
				ParamBuilder&	addChecker(void(*ft)());
				CommandParam*	build();

		};
};

void	validChan();
void	validKey();
void	joinChanRequest();
#endif
