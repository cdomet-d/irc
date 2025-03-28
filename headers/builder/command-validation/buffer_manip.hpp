/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_manip.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:45:04 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/28 12:51:35 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef N_FORMATMESS_HPP
#define N_FORMATMESS_HPP

#include "Client.hpp"
#include "typedef.hpp"

namespace buffer_manip {
	bool prepareCommand(Client &sender);
	stringVec vectorSplit(std::string &s, char del);
}; // namespace buffer_manip

#endif
