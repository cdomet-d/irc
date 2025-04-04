/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:43:23 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/04 13:39:45 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedef.hpp"
#include <iostream>

namespace print {
	void charByChar(const std::string &buf);
	void cmdParam(const stringVec &obj, std::string where);
	void modeEnumToString(e_mdeset set_, e_mdetype type_);
	void modeArgs(const stringVec &mdestr, const stringVec &modeargs,
				  const std::string &where);
	void argument(const stringVec::const_iterator &it, size_t width);
	size_t getLargerArg(const stringVec &arr);
} // namespace print
