/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_formatMess.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlotte <charlotte@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:45:04 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/27 09:49:51 by charlotte        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef N_FORMATMESS_HPP
#define N_FORMATMESS_HPP

#include "Client.hpp"
#include "typedef.hpp"

namespace formatMess {
	bool assess(Client &sender);
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

