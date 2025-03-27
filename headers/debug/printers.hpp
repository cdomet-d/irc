/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:43:23 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/27 14:20:05 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedef.hpp"
#include <iostream>

namespace print {
	void charByChar(const std::string &buf);
	void cmdParam(const stringVec &obj, std::string where);
} // namespace print
