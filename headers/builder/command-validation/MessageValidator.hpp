/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageValidator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:45:04 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/07 14:23:23 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGEVALIDATOR_HPP
#define MESSAGEVALIDATOR_HPP

#include "Client.hpp"
#include "typedef.hpp"
#include <string>
#include <vector>

class MessageValidator {
  public:
	/*                               ORTHODOX CLASS                           */
	MessageValidator(void);
	MessageValidator(const MessageValidator &rhs);
	~MessageValidator(void);
	MessageValidator &operator=(const MessageValidator &rhs);

	/*                               METHODS                                  */
	static void assess(const Client &sender);
	/*                               GETTERS                                  */

	/*                               SETTERS                                  */

  private:
	/*                               METHODS                                  */
	static bool hasPrefix(const std::string &mess,
						  const std::string &cliPrefix);
	static bool hasTrailing(const std::string &mess);
	static bool lenIsValid(const std::string &mess);
	static std::string getTrailing(const std::string &mess);
	static std::string trimPrefix(const std::string &mess);
	static stringVec vectorSplit(std::string &s, const std::string &del);
	static stringVec StructureIsValid(const std::string &mess);
};

#endif
