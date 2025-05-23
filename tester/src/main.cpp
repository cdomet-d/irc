/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:40:59 by csweetin          #+#    #+#             */
/*   Updated: 2025/04/15 14:30:12 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testers.hpp"

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "wrong arg" << std::endl;
		return (1);
	}
	std::string cmd[14]
		= { "reg",	"pass", "nick", "user", "invite", "join", "kick",
			"mode", "part", "quit", "msg",	"topic",  "who",  "trail" };
	size_t i = 0;
	while (i < 14 && argv[1] != cmd[i])
		i++;
	switch (i) {
	// registration
	case 0:
		if (test("tester-scripts/test-registration.sh",
				 "expected-outputs/registration_output.tx", "Registration:"))
			return (1);
		break;
	// PASS
	case 1:
		if (test("tester-scripts/test-pass.sh",
				 "expected-outputs/pass_output.tx", "PASS:"))
			return (1);
		break;
	// NICK
	case 2:
		if (test("tester-scripts/test-nick.sh",
				 "expected-outputs/nick_output.tx", "NICK:"))
			return (1);
		break;
	// USER
	case 3:
		if (test("tester-scripts/test-user.sh",
				 "expected-outputs/user_output.tx", "USER:"))
			return (1);
		break;
	//INVITE
	case 4:
		if (test("tester-scripts/test-invite.sh",
				 "expected-outputs/invite_output.tx", "INVITE:"))
			return (1);
		break;
	// JOIN
	case 5:
		if (test("tester-scripts/test-join.sh",
				 "expected-outputs/join_output.tx", "JOIN:"))
			return (1);
		break;
	// KICK
	case 6:
		if (test("tester-scripts/test-kick.sh",
				 "expected-outputs/kick_output.tx", "KICK:"))
			return (1);
		break;
	// MODE
	case 7:
		if (test("tester-scripts/test-mode.sh",
				 "expected-outputs/mode_output.tx", "MODE:"))
			return (1);
		break;
	// PART
	case 8:
		if (test("tester-scripts/test-part.sh",
				 "expected-outputs/part_output.tx", "PART:"))
			return (1);
		break;
	// QUIT
	case 9:
		if (test("tester-scripts/test-quit.sh",
				 "expected-outputs/quit_output.tx", "QUIT:"))
			return (1);
		break;
	// PRIVMSG
	case 10:
		if (test("tester-scripts/test-privmsg.sh",
				 "expected-outputs/privmsg_output.tx", "PRIVMSG:"))
			return (1);
		break;
	// TOPIC
	case 11:
		if (test("tester-scripts/test-topic.sh",
				 "expected-outputs/topic_output.tx", "TOPIC:"))
			return (1);
		break;
	// WHO
	case 12:
		if (test("tester-scripts/test-who.sh",
				 "expected-outputs/who_output.tx", "WHO:"))
			return (1);
		break;
	// TRAILING
	case 13:
		if (test("tester-scripts/test-trailing.sh",
				 "expected-outputs/trailing_output.tx", "TRAILING:"))
			return (1);
		break;
	default:
		std::cout << "wrong test name\n";
	}
	return (0);
}
