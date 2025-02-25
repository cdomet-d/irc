/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Builder.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:06:23 by csweetin          #+#    #+#             */
/*   Updated: 2025/02/24 18:20:57 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

what product ? a command
what makes up that product ? permission, parameters, executor
what are the steps to build each part ?
what are the parameters or options for each steps ?

steps :
- parsing

- building
	-permission
	-param
		-checkers
	-executor
	-build

- register ?

- execute with director

------------------------------------------
buffer = string to parse ex : "/join #channel_name"

parsing : check bnf, rm "/" and "#", put in std::vector<std::string>>
	res -> tab[0] : join
			tab[1] : channel_name

if (tab[0] == join)
-> Join		cm(tab[1]); //cree un objet de la classe Join.hpp
-> checkers : 	cm.enoughParam()
			 	cm.validChan()
			 	cm.joinChanRequest()
-> executor :  	cm.addToChan()

*/


#ifndef BUILDER_HPP
# define BUILDER_HPP

class Builder
{
public:
	/*                               ORTHODOX CLASS                           */
	virtual ~Builder(void);

	/*                               METHODS                                  */
	
	/*                               GETTERS                                  */
	
	/*                               SETTERS                                  */
};

#endif
