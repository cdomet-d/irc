/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:23:26 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/25 09:46:45 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "Utils.hpp"
#include <string>
#include <unistd.h>
#include <vector>

typedef std::vector< std::string > stringVec;

enum param { prefix_, cmd_, target_, content_ };

class Msg {
  public:
	/*                               ORTHODOX CLASS                           */
	Msg(void);
	~Msg(void);

	/*                               METHODS                                  */
	bool processBuf();
	void clear();
	void removeNl();
	bool rplIs(const std::string &expected) const;
	void trimConsecutiveSpaces();
	ssize_t _recv(const int fd);
	void clearCmdParam();

	/*                               GETTERS                                  */
	const std::string &getRcv() const;

	/*                               SETTERS                                  */
	void setRcv();

	stringVec cmdParam_;

  private:
	void trimUsername();

	Msg(const Msg &rhs);
	Msg &operator=(const Msg &rhs);
	std::string rcv_;
	char rcvbuf[1024];
};

#endif