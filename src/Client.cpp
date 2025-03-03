/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:14:26 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/03 15:34:22 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

/* constructors & destructor */
Client::Client(void)
{
	//std::cout << "Client default constructor called" << std::endl;
}

Client::Client(const Client& obj)
{
	//std::cout << "Client copy constructor called" << std::endl;
	*this = obj;
}

Client::~Client(void)
{
	//std::cout << "Client destructor called" << std::endl;
}

/*operators*/
Client&	Client::operator=(const Client& obj)
{
	//std::cout << "Client copy assignment operator called" << std::endl;
	if (this != &obj)
	{
		this->registration = obj.registration;
	}
	return (*this);
}

/*method*/
int	Client::getRegistration(void)
{
	return (this->registration);
}

void	Client::setRegistration(int stage)
{
	this->registration = stage;
}