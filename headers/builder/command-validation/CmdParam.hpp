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

//TODO: ajouter un rmParam ?

class CmdParam {
  public:
	/*                               CONSTRUCTORS                             */
	~CmdParam(void);

	/*                               METHODS                                  */
	std::string &operator[](unsigned int i);
	CmdParam &operator=(const CmdParam &rhs);

	/*                               GETTERS                                  */
	bool getOpt(void) const;
	bool getList() const;
	size_t getParamSize(void) const;
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
		ParamBuilder &isList(bool list);

	  private:
		bool opt_;
		bool list_;
		stringVec param_;
	};

  private:
	/*                               MEMBERS                                  */
	bool opt_;
	bool list_;
	stringVec param_;

	// private constructor
	CmdParam(stringVec &param, const bool opt, const bool list);
	CmdParam(const CmdParam &rhs);
};

#endif
