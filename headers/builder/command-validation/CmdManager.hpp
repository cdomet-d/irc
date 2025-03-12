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

class CmdManager {
  public:
	/*                               CONSTRUCTORS                             */
	CmdManager(void);
	~CmdManager(void);

	/*                               METHODS                                  */
	void executeCm(CmdSpec &cm);
	void generateCmds();
	void log(CmdSpec *cm);

	/*                               GETTERS                                  */
	CmdSpec &getCmd(const std::string &cmName);

  private:
	/*                               MEMBERS                                  */
	std::map< std::string, CmdSpec * > commandList_;
};

#endif
