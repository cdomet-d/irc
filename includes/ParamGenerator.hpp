//HEADER

#ifndef PARAMGENERATOR_HPP
# define PARAMGENERATOR_HPP

# include <iostream>
# include "CommandParam.hpp"

class	ParamGenerator
{
	private:
		std::vector<CommandParam>	params;
		std::vector<CommandParam>	paramsOpt;
	public:
		//constructors & destructor
		ParamGenerator(void);
		ParamGenerator(const ParamGenerator& obj);
		~ParamGenerator(void);

		//operators
		ParamGenerator&		operator=(const ParamGenerator& obj);
		CommandParam&		operator[](unsigned int i);

		//methods
		ParamGenerator&	addParam(const CommandParam& param);
		ParamGenerator&	addOptParam(CommandParam& paramOpt);

		//getters
		std::vector<CommandParam>&	getParams(void);
		std::vector<CommandParam>&	getOptParams(void);
};

#endif
