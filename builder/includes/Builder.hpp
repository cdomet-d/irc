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
buffer = string to parse ex : "/join #channel_name"

//sans builder :
parsing : check bnf, rm "/" and "#", put in std::vector<std::string>>
	res -> tab[0] : join
			tab[1] : channel_name

if (tab[0] == join)
-> Join		cm(tab[1]); //cree un objet de la classe Join.hpp
-> checkers : 	cm.enoughParam()
			 	cm.validChan()
			 	cm.joinChanRequest()
-> executor :  	cm.addToChan()

//avec builder :
commandSpec	Join = commandSpec::builder()
						.setName("JOIN")
						.
	




*/

/*exemple de simon
//avec builder pattern :
commandManager.registerCommand(CommandSpec::Builder()
	.name("PART")
	.argument("channels", GenericArguments::list<Channel>(new ChannelCommandElement(false)))
	.argument("message", GenericArguments::optional(GenericArguments::string()))
	.middleware(new RegisteredUserMiddleware())
	.executor(new PartCommand())
	.build()
);

//sans builder pattern :
vector<pair<string, CommandElement *> > partCmdArgs;
partCmdArgs.push_back(std::pair<std::string, CommandElement *>("channels", new ChannelCommandElement()));
partCmdArgs.push_back(std::pair<std::string, CommandElement *>("message", GenericArguments::optional(GenericArguments::string())));
commandManager.registerCommand(new CommandSpec("PART", partCmdArgs, new RegisteredUserMiddleware(), new PartCommand());
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
