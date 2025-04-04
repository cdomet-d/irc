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
	CmdParam(const bool opt, const bool list);
	CmdParam(const CmdParam &rhs);
	~CmdParam(void);

	/*                               METHODS                                  */
	bool empty();
	bool isList() const;
	bool isOpt(void) const;
	CmdParam &operator=(const CmdParam &rhs);
	size_t size(void) const;
	std::string &operator[](unsigned int i);
	const std::string &operator[](unsigned int i) const;
	void addOne(unsigned int pos);
	void clean(void);
	void rmParam(unsigned int pos);
	void trimParam(int paramIdx, int startPos, int lenToTrim);

	/*                               GETTERS                                  */
	const stringVec &getInnerParam(void) const;

	/*                               SETTERS                                  */
	void setOneParam(std::string &buffer);
	void setParamList(const stringVec &buffer);

  private:
	/*                               MEMBERS                                  */
	bool opt_;
	bool list_;
	stringVec innerParam_;
};

#endif
