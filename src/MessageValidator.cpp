/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageValidator.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:45:07 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/03 19:05:20 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MessageValidator.hpp"
#include <algorithm>
#include <iostream>
#define MESSAGE_TERMINATION "\r\n"

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */

MessageValidator::MessageValidator(void) {}

MessageValidator::MessageValidator(const MessageValidator &rhs) {
	*this = rhs;
}

MessageValidator::~MessageValidator(void) {}

MessageValidator &MessageValidator::operator=(const MessageValidator &rhs) {
	// rhs instructions
	return *this;
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */
bool MessageValidator::hasPrefix(const std::string &mess) {
	// if (mess.at(0) == ':')
}

bool MessageValidator::hasTrailing(const std::string &mess) {}

bool MessageValidator::lenIsValid(const std::string &mess) {

	if (mess.empty())
		return false;
	if (mess.size() > 512) {
		// send 417 - ERR_INPUTTOOLONG
		std::cerr << "Input too long" << std::endl;
		return false;
	}
	return true;
}

std::string MessageValidator::getTrailing(const std::string &mess) {}
std::string MessageValidator::trimPrefix(const std::string &mess) {}
stringVec MessageValidator::vectorSplit(std::string &s,
										const std::string &del) {}
stringVec MessageValidator::StructureIsValid(const std::string &mess) {}

/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */

/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */