/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParamCheckers.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:15:18 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/03 17:18:22 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandParam.hpp"

int	validChan(std::string& channel)
{
	if (channel[0] != '#')
	{
		std::cerr << channel << " :No such channel" << std::endl;
		//trouver un moyen de supprimer ce param pour pas qu'il soit la lors de l'execution
	}
}

// int	validKey(std::string& param)
// {

// }

int	joinChanRequest(std::string& param, Client& client)
{
	//supprimer chaque channel faux, ainsi que toutes les keys \
	pour qu'il reste que les channel valide a join pour l'exec
												
}