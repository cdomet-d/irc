/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:14:19 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/03 15:14:21 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOIN_HPP
# define JOIN_HPP

# include <iostream>
# include "Executor.hpp"

class	Join : public Executor
{
	private:
		//attributes
	public:
		//constructors & destructor
		Join(void);
		Join(const Join& obj);
		~Join(void);

		//operators
		Join&	operator=(const Join& obj);

		//method
		void	execute();
};

#endif
