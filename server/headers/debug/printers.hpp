/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:43:23 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/24 19:26:12 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTERS_HPP
#define PRINTERS_HPP

#include "typedef.hpp"
#include <ctime>
#include <iomanip>
#include <iostream>

namespace print {
	std::string timeStamp();
	void charByChar(const std::string &buf);
	void cmdParam(const stringVec &obj, std::string where);
	void modeEnumToString(e_mdeset set_, e_mdetype type_);
	void modeArgs(const stringVec &mdestr, const stringVec &modeargs,
				  const std::string &where);
	void argument(const stringVec::const_iterator &it, size_t width);
	size_t getLargerArg(const stringVec &arr);
	template < typename MapType >
	void map(const MapType &map, const std::string &what) {
		std::cout << "[" + what + "]" << std::endl;
		typedef typename MapType::key_type key;
		// typedef typename MapType::value_type val;
		for (typename MapType::const_iterator it = map.begin(); it != map.end();
			 ++it) {

			const key &k = it->first;
			std::cout << std::setw(20) << k << std::endl;
		}
	}
} // namespace print

#endif