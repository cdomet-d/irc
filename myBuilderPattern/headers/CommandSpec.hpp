/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandSpec.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:13:38 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/10 17:27:00 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDSPEC_HPP
# define COMMANDSPEC_HPP

# include <iostream>
# include "CommandParam.hpp"
// # include "Executor.hpp"
// # include "Join.hpp"
# include <map>

typedef enum	p_enum
{
	password,
	nickname,
	username,
	channel,
	key,
	target
};

class	CommandSpec
{
	private:
		std::string										name_;
		int												registrationStage_;
		std::map<p_enum, std::vector<CommandParam*> >	params_;
		std::vector<void(*)(CommandSpec&)>				checkers_;
		void(*cmExecutor_)(CommandSpec& cmd);
		bool											cancelled_;
		Client&											sender;
		
		//constructor
		CommandSpec(std::string name, int registrationStage, std::map<p_enum, std::vector<CommandParam*> > params, \
					std::vector<void(*)(CommandSpec&)> checkers, void(*cmExecutor_)(CommandSpec& cmd));
	public:
		//destructor
		~CommandSpec(void);

		//method
		CommandSpec&	process(std::string& buffer, Client& client);

		//getters
		std::string		getName(void);
		bool			getCancelled(void);
		// Executor*		getExecutor(void);
		// int				(*getChecker(unsigned int i))(std::string&);
		// size_t			getCheckerSize(void);
		
		
		// nested class --------------------------------------------------------
		class	CommandBuilder //builds a command
		{
			private:
				std::string										name_;
				int												registrationStage_;
				std::map<p_enum, std::vector<CommandParam*> >	params_;
				std::vector<void(*)(CommandSpec& cmd)>			checkers_;
				void(*cmExecutor_)(CommandSpec& cmd);
			public:
				//constructors & destructor
				CommandBuilder(void);
				~CommandBuilder(void);

				//methods
				CommandBuilder&	Name(const std::string& name);
				CommandBuilder&	Registration(int stage);
				CommandBuilder&	Parameters(CommandParam* param);
				CommandBuilder&	addChecker(void(*ft)(CommandSpec& cmd));
				CommandBuilder&	CmExecutor(void(*ft)(CommandSpec& cmd));
				CommandSpec*	build();
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

//a la place donner CommandSpec a tous ? et mettre une instance Client dans CommandSpec ?

#endif

