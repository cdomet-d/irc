/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinRequestCheck.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:50:33 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/26 13:17:58 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOINREQUESTCHECK_HPP
#define JOINREQUESTCHECK_HPP

#include "CmdSpec.hpp"

namespace joinCheck {
	bool reachedChanLimit(Channel &chan, Client &sender);
	bool hasInvite(Channel &chan, Client &sender);
	bool validKey(Channel &chan, CmdParam &keys, size_t i, Client &sender);
	bool reachedCliChanLimit(Channel &chan, Client &sender);
}; // namespace joinCheck

#endif