/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlotte <charlotte@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:40:59 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/26 10:13:36 by charlotte        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testers.hpp"

int main() {
	//registration
	if (test("tester-scripts/test-registration.sh", "expected-outputs/registration_output.tx", "Registration:"))
		return (1);
	//PASS
	if (test("tester-scripts/test-pass.sh", "expected-outputs/pass_output.tx", "PASS:"))
		return (1);
	//NICK
	if (test("tester-scripts/test-nick.sh", "expected-outputs/nick_output.tx", "NICK:"))
		return (1);
	//USER
	if (test("tester-scripts/test-user.sh", "expected-outputs/user_output.tx", "USER:"))
		return (1);
	//INVITE
	// if (test("tester-scripts/test-invite.sh", "expected-outputs/invite_output.tx", "INVITE:"))
	// 	return (1);
	//JOIN
	// if (test("tester-scripts/test-join.sh", "expected-outputs/join_output.tx", "JOIN:"))
		// return (1);
	return (0);
}
