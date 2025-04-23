/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_manip.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:45:04 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/23 17:26:12 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_MANIP_HPP
#define BUFFER_MANIP_HPP

#include "Client.hpp"
#include "typedef.hpp"

namespace buffer_manip {
	bool prepareCommand(Client &sender);
	stringVec vectorSplit(std::string &s, const char &del);
}; // namespace buffer_manip

#endif
