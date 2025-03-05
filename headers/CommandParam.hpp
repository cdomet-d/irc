/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandParam.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:13:44 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/03 17:28:26 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDPARAM_HPP
# define COMMANDPARAM_HPP

# include <iostream>
# include <vector>
# include "Client.hpp"

class	CommandParam
{
	private:
		std::vector<std::string>			param;
		std::vector<int(*)(std::string&)>	checkers; //faire un template ??
	public:
		//constructors & destructor
		CommandParam(void);
		CommandParam(std::vector<std::string> param, std::vector<int(*)(std::string&)> checkers);
		CommandParam(const CommandParam& obj);
		~CommandParam(void);

		//operators
		CommandParam&	operator=(const CommandParam& obj);
		std::string&	operator[](unsigned int i);

		//methods
		std::vector<std::string>&	getParam(void);
		size_t						getParamSize(void);
		int							(*getChecker(unsigned int i))(std::string&);
		size_t						getCheckerSize(void);

		//--------------------nested class----------------------
		class	ParamBuilder
		{
			private:
				std::vector<std::string>			param;
				std::vector<int(*)(std::string&)>	checkers;
			public:
				//constructors & destructor
				ParamBuilder(void);
				ParamBuilder(const ParamBuilder& obj);
				~ParamBuilder(void);

				//operators
				ParamBuilder&		operator=(const ParamBuilder& obj);

				//methods
				ParamBuilder&	addChecker(int(*ft)(std::string&));
				CommandParam*	build();

		};
};

int	pwMatch(std::string& password);
int	isRegistered(Client& client);
int	validNick(std::string& nickname);
int	validUser(std::string& username);
int	validChan(std::string& channel);
// int	validKey(std::string& param);
int	joinChanRequest(std::string& channel, std::string& key, Client& client);
int	validTarget(std::string& targetNickname);
int	validInvite(std::string& channel, std::string& targetNickname);
int	OnChan(std::string& channel, Client& client);
int	hasChanPriv(std::string& channel, Client& client);
int	validKick(std::string& channel, std::string& targetNickname);
int	validMode(/*??*/);
int	validMess(CommandParam& param);


#endif
