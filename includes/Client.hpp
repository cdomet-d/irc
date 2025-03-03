/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:13:58 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/03 15:14:00 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>

class	Client
{
	private:
		//attributes
		int	registration;
	public:
		//constructors & destructor
		Client(void);
		Client(const Client& obj);
		~Client(void);

		//operators
		Client&	operator=(const Client& obj);
};

#endif
