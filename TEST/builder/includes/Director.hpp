/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Director.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:25:56 by csweetin          #+#    #+#             */
/*   Updated: 2025/02/26 15:30:07 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef DIRECTOR_HPP
# define DIRECTOR_HPP

# include <map>
# include <iostream>
# include "CmBuilder.hpp"

class Director
{
public:
	/*                               ORTHODOX CLASS                           */
	Director(void);
	Director(const Director &rhs);
	~Director(void);
	Director &operator=(const Director &rhs);

	/*                               METHODS                                  */
	void	buildCommands();

private:
	std::map<std::string, CmBuilder>	cmds; //stock les moules des commandes
};

#endif
