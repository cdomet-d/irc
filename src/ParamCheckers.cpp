/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParamCheckers.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:15:18 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/03 15:15:20 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandParam.hpp"

void	validChan(std::string& param)
{
	if (param[0] != '#')
		std::cerr << param << " :No such channel" << std::endl;
}

void	validKey(std::string& param)
{

}

void	joinChanRequest(std::string& param)
{
	
}