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
							.requirement(3)
							.addParam(CmParam(channel))
							.addParam(CmParam(string of channel), optionnal)
							.addParam(CmParam(string of keys), optionnal)
							.addExecutor(*function)
							.build()

	register(Join);
	*/
}