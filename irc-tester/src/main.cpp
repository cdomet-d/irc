/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:40:59 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/25 16:51:46 by csweetin         ###   ########.fr       */
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
	//INVITE
	// if (test("tester-scripts/test-invite.sh", "expected-outputs/invite_output.tx", "INVITE:"))
	// 	return (1);
	
	return (0);
}
