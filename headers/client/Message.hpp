/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:17:29 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/27 17:38:51 by cdomet-d         ###   ########.fr       */
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
	const std::string getMess() const;
	const std::string getCmd() const;
	const stringVec &getCmdParam();

	/*                               SETTERS                                  */
	void setMess(std::string buffer);
	void setCmdParam(const stringVec &splitBuffer);
	void setTrailingParam(const std::string &trail);

	/*                               METHODS                                  */
	bool emptyBuff();
	bool hasPrefix(const std::string &cliPrefix);
	bool hasTrailing();
	bool isCap();
	bool lenIsValid(const Client &sender);
	std::string::size_type evaluateTermination() const;
	void clearCmdParam();
	void clearMess();
	void formatMode();
	void removeNewlines();
	void updateMess();

  private:
	Message(const Message &rhs);
	Message &operator=(const Message &rhs);

	// members
	std::string message_;
	std::string leftover_;
	std::string trailing_;
	stringVec cmdParam_;
};

#endif
