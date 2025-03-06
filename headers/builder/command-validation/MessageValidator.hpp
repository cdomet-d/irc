/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageValidator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:45:04 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/06 14:37:04 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGEVALIDATOR_HPP
#define MESSAGEVALIDATOR_HPP

#include <string>
#include <vector>
#include "typedef.hpp"

class MessageValidator {
  public:
	/*                               ORTHODOX CLASS                           */
	MessageValidator(void);
	MessageValidator(const MessageValidator &rhs);
	~MessageValidator(void);
	MessageValidator &operator=(const MessageValidator &rhs);

	/*                               METHODS                                  */
	static bool hasPrefix(const std::string &mess);
	static bool hasTrailing(const std::string &mess);
	static bool lenIsValid(const std::string &mess);
	static std::string getTrailing(const std::string &mess);
	static std::string trimPrefix(const std::string &mess);
	static stringVec vectorSplit(std::string &s, const std::string &del);
	static stringVec StructureIsValid(const std::string &mess);
	/*                               GETTERS                                  */

	/*                               SETTERS                                  */
  private:
};

#endif
