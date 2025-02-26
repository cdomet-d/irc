/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Builder.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:06:23 by csweetin          #+#    #+#             */
/*   Updated: 2025/02/25 17:39:28 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
steps :
- parsing

- building
	-permission
	-param
		-checkers
	-executor
	-build

- register

- execute with director

------------------------------------------
buffer = "/join #channel_name"

//sans builder :
parsing : check bnf, rm "/" and "#", put in std::vector<std::string>>
	res -> tab[0] : join
		   tab[1] : channel_name

if (tab[0] == join)
-> Join		cm(tab[1], Client, Channel); //cree un objet de la classe Join.hpp
-> checkers : 	cm.enoughParam()
			 	cm.validChan()
			 	cm.joinChanRequest()
-> executor :  	cm.addToChan()

//avec builder :
- crée le moule de la commande (cf. Director.cpp)
- enregistrer la commande dans un std::map
- lorsqu'on recoit un buffer on va chercher la commande appropriée dans la map \
	on lui donne le buffer et on execute la commande


*/


#ifndef CMBUILDER_HPP
# define CMBUILDER_HPP

# include <iostream>

class CmBuilder
{
public:
	/*                               ORTHODOX CLASS                           */
	CmBuilder(void);
	CmBuilder(const CmBuilder &rhs);
	~CmBuilder(void);
	CmBuilder &operator=(const CmBuilder &rhs);

	/*                               METHODS                                  */
	
	/*                               GETTERS                                  */
	
	/*                               SETTERS                                  */
	class Builder
	{
	public:
		/*                               ORTHODOX CLASS                           */
		Builder(void);
		Builder(const Builder &rhs);
		~Builder(void);
		Builder &operator=(const Builder &rhs);
	
		/*                               METHODS                                  */
		
		/*                               GETTERS                                  */
		
		/*                               SETTERS                                  */
		//setName() sets CmBuilder name or do i need an attribute name in Builder?
		//setRequirement()
		//setParams()
		//setExecutor()
		//build() returns an object CmBuilder
	private:
		
	};	

private:
	std::string	name;//maybe not necessary
	int			requirement;//0: PASS, 1: NICK, 2: USER, 3: registration complete
	//CmParam	parameters;
	//Executor*	function; objet d'une classe abstraite dont herite chaque commande qui aura sa fonction execute ?
};

#endif


