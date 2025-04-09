/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:40:59 by csweetin          #+#    #+#             */
/*   Updated: 2025/04/03 15:59:23 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testers.hpp"

int main() {
  // registration
  if (test("tester-scripts/test-registration.sh",
           "expected-outputs/registration_output.tx", "Registration:"))
    return (1);
  // PASS
  if (test("tester-scripts/test-pass.sh", "expected-outputs/pass_output.tx",
           "PASS:"))
    return (1);
  // NICK
  if (test("tester-scripts/test-nick.sh", "expected-outputs/nick_output.tx",
           "NICK:"))
    return (1);
  // USER
  if (test("tester-scripts/test-user.sh", "expected-outputs/user_output.tx",
           "USER:"))
    return (1);
  // INVITE
  if (test("tester-scripts/test-invite.sh", "expected-outputs/invite_output.tx",
           "INVITE:"))
    return (1);
  // JOIN
  if (test("tester-scripts/test-join.sh", "expected-outputs/join_output.tx",
           "JOIN:"))
    return (1);
  // KICK
  if (test("tester-scripts/test-kick.sh", "expected-outputs/kick_output.tx",
           "KICK:"))
    return (1);
  // MODE
  if (test("tester-scripts/test-mode.sh", "expected-outputs/mode_output.tx",
           "MODE:"))
    return (1);
  // PART
  if (test("tester-scripts/test-part.sh", "expected-outputs/part_output.tx",
           "PART:"))
    return (1);
  // QUIT
  if (test("tester-scripts/test-quit.sh", "expected-outputs/quit_output.tx",
           "QUIT:"))
    return (1);
  // PRIVMSG
  if (test("tester-scripts/test-privmsg.sh",
           "expected-outputs/privmsg_output.tx", "PRIVMSG:"))
    return (1);
  // TOPIC
  if (test("tester-scripts/test-topic.sh", "expected-outputs/topic_output.tx",
           "TOPIC:"))
    return (1);
  return (0);
}
