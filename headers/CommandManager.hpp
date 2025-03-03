/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:14:04 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/03 15:38:54 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDMANAGER_HPP
# define COMMANDMANAGER_HPP

# include <iostream>
# include <map>
# include "CommandSpec.hpp"

class	CommandManager
{
	private:
		std::map<std::string, CommandSpec*>	commandList;
	public:
		//constructors & destructor
		CommandManager(void);
		CommandManager(const CommandManager& obj);
		~CommandManager(void);

		//operators
		CommandManager&	operator=(const CommandManager& obj);

		//methods
		void			generateCmds();
		CommandSpec&	getCmd(const std::string& cmName);
		void			executeCm(CommandSpec& cm);
		void			log(CommandSpec* cm);
};

#endif
