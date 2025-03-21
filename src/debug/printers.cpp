/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:42:32 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/21 13:48:26 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printers.hpp"

void print::charByChar(const std::string &buf) {
	for (std::string::size_type i = 0; i < buf.size(); ++i) {
		if (buf[i] == 10)
			std::cout << "[" << (int)buf[i] << "]";
		if (buf[i] == 13)
			std::cout << "[" << (int)buf[i] << "]";
		else
			std::cout << buf[i];
	}
	std::cout << std::endl;
}

void print::cmdParam(const stringVec &obj, std::string where) {
	std::cout << "[" << std::endl;
	for (stringVec::const_iterator it = obj.begin(); it != obj.end(); ++it) {
		if ((*it).empty())
			std::cout << "\t" + where + ":\t" << "[...]" << std::endl;
		else
			std::cout << "\t" + where + ":\t" << *it << std::endl;
	}
	std::cout << "]" << std::endl;
}