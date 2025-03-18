/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageValidator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:45:04 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/18 16:07:43 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGEVALIDATOR_HPP
#define MESSAGEVALIDATOR_HPP

#include "Client.hpp"
#include "typedef.hpp"

namespace messageValidator {
bool assess(Client &sender);
void printCmdParam(const stringVec &obj, std::string where);
stringVec vectorSplit(std::string &s, char del);

namespace priv {
bool hasPrefix(std::string &mess, const std::string &cliPrefix);
bool hasTrailing(std::string &mess, std::string &trailing);
bool lenIsValid(const std::string &mess, const Client &sender);
std::string removeNewlines(const std::string &input);
void formatMode(Client &sender);
} // namespace priv
}; // namespace messageValidator

#endif
