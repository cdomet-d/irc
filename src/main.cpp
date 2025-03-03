#include <iostream>
#include "CommandManager.hpp"
#include "Client.hpp"
#include "MessageValidator.hpp"

int	main(void)
{
	std::string message = "Hello \r\n yes";
	MessageValidator::hasTermination(message);
}