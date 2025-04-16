#include "Message.hpp"

static bool isConsecutiveSpace(char left, char right) {
	return (left == ' ' && right == ' ');
}

std::string::size_type Msg::evalTerm() const {
	if (message_.find("\r\n") != std::string::npos)
		return 2;
	if (message_.find("\n") != std::string::npos)
		return 1;
	return std::string::npos;
}

void Msg::removeNl() {
	std::string::size_type termSize = evaluateTermination();
	if (termSize == std::string::npos) {
		message_.clear();
		return;
	}
	std::string::size_type newline =
		(termSize == 2 ? message_.find("\r\n") : message_.find("\n"));
	leftover_ = message_.substr(newline + termSize);
	message_.erase(message_.begin() + newline, message_.end());
	return;
}

void Msg::trimConsecutiveSpaces() {
	std::string::iterator newEnd =
		std::unique(message_.begin(), message_.end(), isConsecutiveSpace);
	if (newEnd != message_.end())
		message_.erase(newEnd, message_.end());
}

stringVec Msg::vectorSplit(std::string &s, char del) {
	stringVec result;
	std::string token;

	std::istringstream stream(s);
	while (std::getline(stream, token, del))
		result.push_back(token);
	return (result);
}

void Msg::clear() {
	rcv_.clear();
}

#include "Message.hpp"

/* ************************************************************************** */
/*                               ORTHODOX CLASS                               */
/* ************************************************************************** */

Message::Message(void) {}

Message::Message(const Message &rhs)
{
	*this = rhs;
}

Message::~Message(void) {}

Message &Message::operator=(const Message &rhs)
{
	// rhs instructions
	return *this;
}

/* ************************************************************************** */
/*                               METHODS                                      */
/* ************************************************************************** */
	
/* ************************************************************************** */
/*                               GETTERS                                      */
/* ************************************************************************** */
	
/* ************************************************************************** */
/*                               SETTERS                                      */
/* ************************************************************************** */