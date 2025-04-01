/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:42:32 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/01 08:34:13 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printers.hpp"
#include <iomanip>

void print::charByChar(const std::string &buf) {
	for (std::string::size_type i = 0; i < buf.size(); ++i) {
		if (buf[i] == 10)
			std::cout << "[" << (int)buf[i] << "]";
		if (buf[i] == 13)
			std::cout << "[" << (int)buf[i] << "]";
		else
			std::cout << buf[i];
	}
}

void print::cmdParam(const stringVec &obj, std::string where) {
	if (obj.empty())
		return std::cout << "[ ... ]" << std::endl, (void)false;
	std::cout << "[" << std::endl;
	for (stringVec::const_iterator it = obj.begin(); it != obj.end(); ++it) {
		if ((*it).empty())
			std::cout << "\t" + where + ":\t" << "[...]" << std::endl;
		else
			std::cout << "\t" + where + ":\t" << *it << std::endl;
	}
	std::cout << "]" << std::endl;
}

void print::modeEnumToString(e_mdeset set_, e_mdetype type_) {
	std::cout << "Set: ";
	switch (set_) {
	case SET_ERR:
		std::cout << "SET_ERR |	";
		break;
	case SET:
		std::cout << "SET | ";
		break;
	case UNSET:
		std::cout << "UNSET | ";
		break;
	default:
		break;
	}

	std::cout << "Type: ";
	switch (type_) {
	case TYPE_ERR:
		std::cout << "TYPE_ERR - Unknown type." << std::endl;
		break;
	case B:
		std::cout << "B: always MUST have a param." << std::endl;
		break;
	case C:
		std::cout << "C: MUST have a param when set, MUST NOT have a param "
					 "when unset."
				  << std::endl;
		break;
	case D:
		std::cout << "D:  MUST NOT have a param." << std::endl;
		break;
	default:
		break;
	}
}

size_t print::getLargerArg(const stringVec &arr) {
	size_t max = 0;
	for (stringVec::const_iterator i = arr.begin(); i != arr.end(); ++i) {
		size_t size = (*i).size();
		if (size > max)
			max = size;
	}
	return max + 2;
}

void print::argument(const stringVec::const_iterator &it, size_t width) {
	if ((*it).empty())
		std::cout << std::setw(width) << std::left << "[...]";
	else
		std::cout << std::setw(width) << std::left << *it;
}

void print::modeArgs(const stringVec &mdestr, const stringVec &modeargs,
					 const std::string &where) {
	bool empty_flags = mdestr.empty();
	bool empty_args = modeargs.empty();
	int awidth = getLargerArg(modeargs);
	int swidth = getLargerArg(mdestr);

	if (swidth < 6)
		swidth = 6;
	if (awidth < 5)
		awidth = 5;

	stringVec::const_iterator j;
	if (!empty_args)
		j = modeargs.begin();
	std::cout << "[ " + where << std::endl;

	std::cout << "\t| " << std::setw(swidth) << std::left << "flags";
	std::cout << " | ";
	std::cout << std::setw(awidth) << std::left << "arg";
	std::cout << " |" << std::endl;
	for (stringVec::const_iterator i = mdestr.begin(); i != mdestr.end(); ++i) {
		if (!empty_flags) {
			std::cout << "\t| ";
			print::argument(i, swidth);
		}
		std::cout << " | ";
		if (!empty_args) {
			print::argument(j, awidth);
			if (j != modeargs.end())
				j++;
			std::cout << " |" << std::endl;
		}
	}
	std::cout << "]" << std::endl;
}