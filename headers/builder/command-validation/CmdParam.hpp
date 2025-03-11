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
		const bool					opt_;
		const std::string			delim_;
		
		//constructor
		CmdParam(std::vector<std::string>& param, const bool opt, \
					const std::string& delim);

	public:
		//destructor
		~CmdParam(void);

		//operators
		std::string&	operator[](unsigned int i);

		//methods
		std::vector<std::string>&	getParam(void);
		size_t						getParamSize(void) const;

		//--------------------nested class----------------------
		class	ParamBuilder
		{
			private:
				std::vector<std::string>	param_;
				bool						opt_;
				std::string					delim_;
			public:
				//constructors & destructor
				ParamBuilder(void);
				~ParamBuilder(void);

				//methods
				ParamBuilder&	isOpt(bool opt);
				ParamBuilder&	setDelim(const std::string &delim);
				CmdParam*	build();
		};
};

#endif
