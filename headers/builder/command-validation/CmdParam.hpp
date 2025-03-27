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
#include "typedef.hpp"
#include <iostream>
#include <vector>

class CmdParam {
  public:
	/*                               CONSTRUCTORS                             */
	CmdParam(void);
	CmdParam(const bool opt, const char delim);
	~CmdParam(void);

	/*                               METHODS                                  */
	bool empty();
	CmdParam &operator=(const CmdParam &rhs);
	size_t size(void) const;
	std::string &operator[](unsigned int i);
	void addOne(unsigned int pos);
	void clean(void);
	void rmParam(stringVec::iterator begin, stringVec::iterator end);
	void rmParam(unsigned int pos);

	/*                               GETTERS                                  */
	bool getOpt(void) const;
	char getDelim() const;
	const stringVec &getInnerParam(void) const;

	/*                               SETTERS                                  */
	void setOneParam(std::string &buffer);
	void setParamList(const stringVec &buffer);

  private:
	/*                               MEMBERS                                  */
	bool opt_;
	char delim_;
	stringVec innerParam_;

	// private constructor
	CmdParam(const CmdParam &rhs);
};

#endif
