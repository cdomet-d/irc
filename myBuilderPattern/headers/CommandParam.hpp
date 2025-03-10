/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandParam.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:13:44 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/10 17:26:50 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDPARAM_HPP
# define COMMANDPARAM_HPP

# include <iostream>
# include <vector>
# include "Client.hpp"

class	CommandParam
{
	private:
		std::vector<std::string>	param_;
		bool						opt;
		void(*inputTokenizer)(std::string& buffer, CommandParam& param);
		
		//constructor
		CommandParam(std::vector<std::string> param, std::vector<int(*)(std::string&)> checkers);
	public:
		//destructor
		~CommandParam(void);

		//operators
		CommandParam&	operator=(const CommandParam& obj);
		std::string&	operator[](unsigned int i);

		//methods
		std::vector<std::string>&	getParam(void);
		size_t						getParamSize(void);

		//--------------------nested class----------------------
		class	ParamBuilder
		{
			private:
				std::vector<std::string>	param_;
				bool						opt;
				void(*inputTokenizer)(std::string& buffer, CommandParam& param);
			public:
				//constructors & destructor
				ParamBuilder(void);
				~ParamBuilder(void);

				//methods
				ParamBuilder&	InputTokenizer(void(*ft)(std::string& buffer, CommandParam& param));
				CommandParam*	build();
		};
};

void	splitOnComa(std::string& buffer, CommandParam& param);
// void	splitJoin(std::string& buffer, CommandParam& param);
void	splitOnSpace(std::string& buffer, CommandParam& param);

#endif
