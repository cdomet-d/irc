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

#include "../client/Client.hpp"
#include "typedef.hpp"
#include <iostream>
#include <vector>

class CmdParam {
  public:
	/*                               CONSTRUCTORS                             */
	~CmdParam(void);

	/*                               METHODS                                  */
	std::string &operator[](unsigned int i);
	CmdParam &operator=(const CmdParam &rhs);
	void rmParam(unsigned int pos);
	void rmParam(stringVec::iterator begin, stringVec::iterator end);

	/*                               GETTERS                                  */
	bool getOpt(void) const;
	const std::string &getDelim() const;
	size_t getSize(void) const;
	const stringVec &getParam(void) const;

	/*                               SETTERS                                  */
	void setOne(std::string &buffer);
	void setList(const stringVec &buffer);

	/*                               NESTED CLASS                             */
	class ParamBuilder {
	  public:
		ParamBuilder(void);
		~ParamBuilder(void);

		//methods
		CmdParam *build();
		ParamBuilder &isOpt(bool opt);
		ParamBuilder &isList(const std::string& delim);

	  private:
		bool opt_;
		std::string delim_;
		stringVec param_;
	};

  private:
	/*                               MEMBERS                                  */
	bool opt_;
	std::string delim_;
	stringVec param_;

	// private constructor
	CmdParam(stringVec &param, const bool opt, const std::string& delim);
	CmdParam(const CmdParam &rhs);
};

#endif
