/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:16:46 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/12 16:31:21 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */

Message::Message(void) {}

Message::~Message(void) {}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */
stringVec Message::getCmdParam() {
	return cmdParam_;
}

std::string Message::getBuffer() const {
	return (buffer_);
}

/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */

void Message::setCmdParam(const stringVec &splitBuffer) {
	cmdParam_ = splitBuffer;
}

void Message::setTrailingParam(const std::string &trail) {
	cmdParam_.push_back(trail);
}

void Message::setBuffer(std::string buffer) {
	buffer_ = buffer;
}
