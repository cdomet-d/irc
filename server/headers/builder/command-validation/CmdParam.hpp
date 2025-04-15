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
	CmdParam();
	CmdParam(const bool opt, const bool list);
	CmdParam(const CmdParam &rhs);
	~CmdParam();

	/*                               METHODS                                  */
	bool empty();
	bool isList() const;
	bool isOpt() const;
	CmdParam &operator=(const CmdParam &rhs);
	size_t size() const;
	std::string &operator[](size_t i);
	const std::string &operator[](size_t i) const;
	void addOne(size_t pos);
	void clean();
	void rmParam(size_t pos);
	bool trimParam(size_t paramIdx, size_t lenToTrim);

	/*                               GETTERS                                  */
	const stringVec &getInnerParam() const;

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
