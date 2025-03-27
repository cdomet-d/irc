/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_formatMess.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:45:04 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/27 13:53:16 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef N_FORMATMESS_HPP
#define N_FORMATMESS_HPP

#include "Client.hpp"
#include "typedef.hpp"

namespace format_mess {
	bool assess(Client &sender);
	stringVec vectorSplit(std::string &s, char del);

	namespace priv {

	} // namespace priv
}; // namespace format_mess

#endif
