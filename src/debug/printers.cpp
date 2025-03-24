/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:42:32 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/24 17:51:50 by cdomet-d         ###   ########.fr       */
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
	if (obj.empty())
		std::cout << "[ ... ]" << std::endl;
	std::cout << "[" << std::endl;
	for (stringVec::const_iterator it = obj.begin(); it != obj.end(); ++it) {
		if ((*it).empty())
			std::cout << "\t" + where + ":\t" << "[...]" << std::endl;
		else
			std::cout << "\t" + where + ":\t" << *it << std::endl;
	}
	std::cout << "]" << std::endl;
}

void print::modeEnumToString(e_modeset set_, e_modetype type_) {
	std::cout << "Set: ";
	switch (set_) {
	case SET_ERR:
		std::cout << "SET_ERR" << std::endl;
		break;
	case SET:
		std::cout << "SET" << std::endl;
		break;
	case UNSET:
		std::cout << "UNSET" << std::endl;
		break;
	default:
		break;
	}

	std::cout << "Type: ";
	switch (type_) {
	case TYPE_ERR:
		std::cout << "TYPE_ERR - Unknown type" << std::endl;
		break;
	case B:
		std::cout << "B: always MUST have a param" << std::endl;
		break;
	case C:
		std::cout << "C: MUST have a param when set, MUST NOT have a param when unset" << std::endl;
		break;
	case D:
		std::cout << "D:  MUST NOT have a param" << std::endl;
		break;
	default:
		break;
	}
}
