/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinRequestCheck.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:50:33 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/19 18:36:19 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOINREQUESTCHECK_HPP
# define JOINREQUESTCHECK_HPP

# include "CmdSpec.hpp"

namespace joinCheck {
	bool reachedChanLimit(Channel &chan, Client &sender);
	bool hasInvite(Channel &chan, Client &sender);
	bool validKey(Channel &chan, CmdParam &keys, size_t i, Client &sender);
	bool reachedCliChanLimit(Channel &chan, Client &sender);
};

#endif