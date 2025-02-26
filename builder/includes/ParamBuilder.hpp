//HEADER

#ifndef PARAMBUILDER_HPP
# define PARAMBUILDER_HPP

# include <vector>
# include <iostream>

class ParamBuilder
{
public:
	/*                               ORTHODOX CLASS                           */
	ParamBuilder(void);
	ParamBuilder(const ParamBuilder &rhs);
	~ParamBuilder(void);
	ParamBuilder &operator=(const ParamBuilder &rhs);

	/*                               METHODS                                  */
	/*
		enoughParam()
		validChan()
		onChan()
		hasChanPriv()
		pwMatch()

		validInvite() //INVITE
		joinChanRequest() //JOIN
		validKick() //KICK
		validNick() //NICK
		clientAuth() //OPER
		validMess() //PRIVMSG
		validUser() //USER
	*/
	
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
		//build() returns an object ParamBuilder
		
		/*                               GETTERS                                  */
		
		/*                               SETTERS                                  */

	private:
		
	};	

private:
	std::vector<std::string>	params;
	std::vector<std::string>	OptParams;
	/* OU
		std::vector<std::pair<std::pair<enum, std::string>, *checker>>	params;
		enum c'est le type de l'argument : channel, password, keyword etc
		std::string est a NULL et on le remplie quand on recoit un buffer d'un client
		chercker : la fonction qui va verif la validité du param
	*/

};

#endif
