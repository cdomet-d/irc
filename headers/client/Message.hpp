/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:17:29 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/18 17:00:03 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "typedef.hpp"

class Message {
  public:
	/*                               ORTHODOX CLASS                           */
	Message(void);
	~Message(void);
	std::string &operator[](unsigned int i);

	/*                               GETTERS                                  */
	size_t getSize() const;
	std::string getBuffer() const;
	std::string getCmd() const;
	stringVec &getCmdParam();

	/*                               SETTERS                                  */
	void setBuffer(std::string buffer);
	void setCmdParam(const stringVec &splitBuffer);
	void setTrailingParam(const std::string &trail);

	/*                               METHODS                                  */
	void clearCmdParam();
	void clearBuffer();

  private:
	Message(const Message &rhs);
	Message &operator=(const Message &rhs);

	// members
	std::string buffer_;
	stringVec cmdParam_;
};

#endif
