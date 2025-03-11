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
# define CMDMANAGER_HPP

# include <iostream>
# include <map>
# include "CmdSpec.hpp"

class	CmdManager
{
	private:
		std::map<std::string, CmdSpec*>	commandList;
	public:
		//constructors & destructor
		CmdManager(void);
		CmdManager(const CmdManager& obj);
		~CmdManager(void);

		//operators
		CmdManager&	operator=(const CmdManager& obj);

		//methods
		void			generateCmds();
		CmdSpec&	getCmd(const std::string& cmName);
		void			executeCm(CmdSpec& cm);
		void			log(CmdSpec* cm);
};

#endif
