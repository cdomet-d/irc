/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<<< HEAD:headers/builder/command-validation/n_formatMess.hpp
/*   n_formatMess.hpp                                   :+:      :+:    :+:   */
========
/*   buffer_manip.hpp                                   :+:      :+:    :+:   */
>>>>>>>> main:headers/builder/command-validation/buffer_manip.hpp
/*                                                    +:+ +:+         +:+     */
/*   By: charlotte <charlotte@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:45:04 by cdomet-d          #+#    #+#             */
<<<<<<<< HEAD:headers/builder/command-validation/n_formatMess.hpp
/*   Updated: 2025/03/27 09:49:51 by charlotte        ###   ########.fr       */
========
/*   Updated: 2025/03/28 12:51:35 by cdomet-d         ###   ########.fr       */
>>>>>>>> main:headers/builder/command-validation/buffer_manip.hpp
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
