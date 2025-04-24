/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:24:29 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/24 19:25:45 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

stringVec vectorSplit(std::string &rcv, char del) {
	stringVec result;
	std::string token;

	std::istringstream stream(rcv);
	while (std::getline(stream, token, del))
		result.push_back(token);
	return (result);
}
