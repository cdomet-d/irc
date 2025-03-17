/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageValidator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:45:04 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/14 14:49:59 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGEVALIDATOR_HPP
#define MESSAGEVALIDATOR_HPP

#include "Client.hpp"
#include "typedef.hpp"

class MessageValidator {
  public:
	/*                               METHODS                                  */
	static bool assess(Client &sender);
	static stringVec vectorSplit(std::string &s, char del);

  private:
	/*                               METHODS                                  */
	static bool hasPrefix(std::string &mess, const std::string &cliPrefix);
	static bool hasTrailing(std::string &mess, std::string &trailing);
	static bool lenIsValid(const std::string &mess, const Client &sender);
	static void formatMode(Client &sender);
	static std::string removeNewlines(const std::string &input);
	static void printCmdParam(const stringVec &obj, std::string where);
};

#endif
