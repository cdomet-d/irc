/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatMess.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:45:04 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/21 13:38:04 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORMATMESS_HPP
#define FORMATMESS_HPP

#include "Client.hpp"
#include "typedef.hpp"

namespace formatMess {
	bool assess(Client &sender);
	void printCmdParam(const stringVec &obj, std::string where);
	stringVec vectorSplit(std::string &s, char del);

	namespace priv {
		bool hasPrefix(std::string &mess, const std::string &cliPrefix);
		bool hasTrailing(std::string &mess, std::string &trailing);
		bool lenIsValid(const std::string &mess, const Client &sender);
		std::string removeNewlines(std::string &input);
		std::string::size_type evaluateTermination(const std::string &input);
		void formatMode(Client &sender);
	} // namespace priv
}; // namespace formatMess

#endif
