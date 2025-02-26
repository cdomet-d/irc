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
							.addParam(CmParam::builder(channel)
											.validChan()
											.enoughParam())
							.addParam(CmParam::builder(string of channel), optionnal)
							.addParam(CmParam::builder(string of keys), optionnal)
											.joinChanRequest()
							.addExecutor(*function)
							.build()

	register(Join);
	*/
}