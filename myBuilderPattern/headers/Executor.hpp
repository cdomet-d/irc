/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:14:12 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/03 15:14:14 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_HPP
# define EXECUTOR_HPP

# include <iostream>

class	Executor
{
	private:
		//attributes
	public:
		//constructors & destructor
		Executor(void) {};
		virtual ~Executor(void) {};

		//methods
		virtual void	execute() = 0;
};

#endif
