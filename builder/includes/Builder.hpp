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
what makes up that product ? parameters, 
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
buffer = string to parse ex : "/join #channel"

parsing : check bnf

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
