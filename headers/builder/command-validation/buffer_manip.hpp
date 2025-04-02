/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_manip.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:45:04 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/02 15:40:47 by aljulien         ###   ########.fr       */
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
