/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdParam.hpp                                   	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:13:44 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/10 17:26:50 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDPARAM_HPP
# define CMDPARAM_HPP

# include <iostream>
# include <vector>
# include "../client/Client.hpp"

class	CmdParam
{
	private:
		std::vector<std::string>	param_;
		bool						opt_;
		void(*inputTokenizer_)(std::string& buffer, CmdParam& param);
		
		//constructor
		CmdParam(std::vector<std::string> param, bool opt, \
			void(*inputTokenizer)(std::string& buffer, CmdParam& param));
	public:
		//destructor
		~CmdParam(void);

		//operators
		std::string&	operator[](unsigned int i);

		//methods
		std::vector<std::string>&	getParam(void);
		size_t						getParamSize(void);

		//--------------------nested class----------------------
		class	ParamBuilder
		{
			private:
				std::vector<std::string>	param_;
				bool						opt_;
				void(*inputTokenizer_)(std::string& buffer, CmdParam& param);
			public:
				//constructors & destructor
				ParamBuilder(void);
				~ParamBuilder(void);

				//methods
				ParamBuilder&	isOpt(bool opt);
				ParamBuilder&	InputTokenizer(void(*ft)(std::string& buffer, CmdParam& param));
				CmdParam*	build();
		};
};

void	splitOnComa(std::string& buffer, CmdParam& param);
// void	splitJoin(std::string& buffer, CmdParam& param);
void	splitOnSpace(std::string& buffer, CmdParam& param);

#endif
