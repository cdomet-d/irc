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
		ParamGenerator&	operator=(const ParamGenerator& obj);

		//methods
		ParamGenerator&	addParam(CommandParam& param);
		ParamGenerator&	addOptParam(CommandParam& paramOpt);
};

#endif
