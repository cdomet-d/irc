/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_checkJoin.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:50:33 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/24 16:15:12 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef N_CHECKJOIN_HPP
# define N_CHECKJOIN_HPP

# include "CmdSpec.hpp"

namespace checkJoin {
	bool reachedChanLimit(Channel &chan, Client &sender);
	bool hasInvite(Channel &chan, Client &sender);
	bool validKey(Channel &chan, CmdParam &keys, size_t i, Client &sender);
	bool reachedCliChanLimit(Channel &chan, Client &sender);
};

#endif