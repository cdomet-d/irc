//HEADER

#include "Director.hpp"

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */

Director::Director(void) {}

Director::Director(const Director &rhs)
{
	*this = rhs;
}

Director::~Director(void) {}

Director &Director::operator=(const Director &rhs)
{
	// rhs instructions
	return *this;
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */
	
void	Director::buildCommands()
{
	/*

	CmBuilder	Join = CmBuilder::builder()
							.setName("join")
							.requirement("registration")
							.addParam(channel)
							.addParam(string of channel, optionnal)
							.addParam(string of keys, optionnal)
							.addExecutor(*function)
							.build()


	*/
}