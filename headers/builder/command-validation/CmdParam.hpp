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
#define CMDPARAM_HPP

#include "Client.hpp"
#include <iostream>
#include <vector>

class CmdParam {
  public:
	/*                               CONSTRUCTORS                             */
	~CmdParam(void);

	/*                               METHODS                                  */
	std::string &operator[](unsigned int i);

	/*                               GETTERS                                  */
	bool getOpt(void) const;
	size_t getParamSize(void) const;
	std::vector< std::string > &getParam(void); //TODO: add const ?

	/*                               NESTED CLASS                             */
	class ParamBuilder {
	  public:
		ParamBuilder(void);
		~ParamBuilder(void);

		//methods
		CmdParam *build();
		ParamBuilder &isOpt(bool opt);
		ParamBuilder &setDelim(const std::string &delim);

	  private:
		bool opt_;
		std::string delim_;
		std::vector< std::string > param_;
	};

  private:
	/*                               MEMBERS                                  */
	const bool opt_;
	const std::string delim_;
	std::vector< std::string > param_;

	// private constructor
	CmdParam(std::vector< std::string > &param, const bool opt,
			 const std::string &delim);
};

#endif
