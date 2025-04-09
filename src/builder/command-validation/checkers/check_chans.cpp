/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_chans.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:03:05 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/09 13:40:37 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printers.hpp"
#include "validator.hpp"
#include <algorithm>

bool check::chan(CmdSpec &cmd, size_t idx) {
  std::string channel;
  if (cmd.getName() == "PRIVMSG")
    channel = cmd[target_][idx];
  else
    channel = cmd[channel_][idx];

  if (!check::exists(channel, cmd.serv_.getAllChan())) {
    reply::send_(cmd.getSendFd(),
                 ERR_NOSUCHCHANNEL(cmd.getSendNick(), channel));
    return (false);
  }
  stringVec userChan = cmd.getSender().getJoinedChans();
  if (!check::chans_::onChan(channel, userChan)) {
    reply::send_(cmd.getSendFd(), ERR_NOTONCHANNEL(cmd.getSendNick(), channel));
    return (false);
  }
  return (true);
}

bool check::chans_::onChan(std::string arg, const stringVec &arr) {
  return std::find(arr.begin(), arr.end(), arg) != arr.end();
}

bool check::chans_::isOp(CmdSpec &cmd, size_t idx) {
  channelMap::const_iterator itChan;

  itChan = cmd.serv_.getAllChan().find(cmd[channel_][idx]);
  Channel chan = *itChan->second;

  if (cmd.getName() == "TOPIC" &&
      (cmd[topic_].empty() || chan.getModes().find('t') == std::string::npos)) {
    return (true);
  }

  clientMap::const_iterator itCl;

  itCl = chan.getOpCli().find(cmd.getSendFd());
  if (itCl == chan.getOpCli().end()) {
    reply::send_(cmd.getSendFd(),
                 ERR_CHANOPRIVSNEEDED(cmd.getSendNick(), chan.getName()));
    return (false);
  }
  return (true);
}
