/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:17:29 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/24 17:13:54 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "typedef.hpp"

class Message {
  public:
	/*                               ORTHODOX CLASS                           */
	Message();
	~Message();
	std::string &operator[](unsigned int i);

	/*                               GETTERS                                  */
	size_t getSize() const;
	const std::string &getMess() const;
	const std::string &getLeft() const;
	const std::string &getCmd() const;
	const stringVec &getCmdParam() const;

	/*                               SETTERS                                  */
	void setMess(const std::string &buffer);
	void setCmdParam(const stringVec &splitBuffer);

	/*                               METHODS                                  */
	// checkers

	bool buffIsEmpty();
	bool hasPrefix(const std::string &cliPrefix);
	bool hasTrailing();
	bool hasValidLen(const Client &sender);
	bool isCap();

	// clearing and updating

	void clear(bool clearLeftover);
	void clearCmdParam();
	void clearMess();
	void updateMess();

	// sanitizing input

	std::string::size_type evaluateTermination(std::string &term) const;
	void cmdToUpper();
	void removeNewlines();
	void trimSpaces();

	// mode formatting

	void formatMode();
	void formatModeFlags(std::string &flagformat);
	void formatModeParam(std::string &paramformat);
	void assignFormattedMode(const std::string &flagformat,
							 const std::string &paramformat,
							 stringVec &modeformat);

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
