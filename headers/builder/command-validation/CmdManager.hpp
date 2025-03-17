/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdManager.hpp                                 	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:14:04 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/03 15:38:54 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDMANAGER_HPP
#define CMDMANAGER_HPP

#include "CmdSpec.hpp"
#include <iostream>
#include <map>

typedef	 std::map< std::string, CmdSpec * > cmdMap;

class CmdManager {
  public:
	/*                               CONSTRUCTORS                             */
	static CmdManager &getManagerInstance();
	~CmdManager(void);

	/*                               METHODS                                  */
	CmdSpec &findCmd(const std::string &cmName);
	void executeCm(CmdSpec &cm);
	void generateCmds();
	void log(CmdSpec *cm);

	/*                               NESTED CLASS                             */
	class CmdNotFoundException : std::exception {
		public:
		const char* what() const throw() {
			return ("Command not found");
		}
	};

  private:
	/*                               MEMBERS                                  */
	cmdMap commandList_;

	// private constructor
	CmdManager(void);
};

#endif
