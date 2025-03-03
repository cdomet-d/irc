//HEADER

#ifndef COMMANDPARAM_HPP
# define COMMANDPARAM_HPP

# include <iostream>
# include <vector>

class	CommandParam
{
	private:
		std::vector<std::string>			param;
		std::vector<void(*)(std::string&)>	checkers;
	public:
		//constructors & destructor
		CommandParam(void);
		CommandParam(std::vector<std::string> param, std::vector<void(*)(std::string&)> checkers);
		CommandParam(const CommandParam& obj);
		~CommandParam(void);

		//operators
		CommandParam&	operator=(const CommandParam& obj);
		std::string&	operator[](unsigned int i);

		//methods
		std::vector<std::string>&	getParam(void) {
			return (this->param);}
		size_t						getParamSize(void) {
			return (this->param.size());}
		void						(*getChecker(unsigned int i))(std::string&) {
			return (checkers[i]);
		}
		size_t						getCheckerSize(void) {
			return (this->checkers.size());}
		//nested class
		class	ParamBuilder
		{
			private:
				std::vector<std::string>			param;
				std::vector<void(*)(std::string&)>	checkers;
			public:
				//constructors & destructor
				ParamBuilder(void);
				ParamBuilder(const ParamBuilder& obj);
				~ParamBuilder(void);

				//operators
				ParamBuilder&		operator=(const ParamBuilder& obj);

				//methods
				ParamBuilder&	addChecker(void(*ft)(std::string&));
				CommandParam*	build();

		};
};

void	validChan(std::string& param);
void	validKey(std::string& param);
void	joinChanRequest(std::string& param);
#endif
