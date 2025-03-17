/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:37:38 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/17 13:13:45 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Reply.hpp"
#include "Log.h"
#include <sys/socket.h>

void sendReply(int fd, std::string reply)
{
	size_t bytes = send(fd, reply.c_str(), strlen(reply.c_str()), MSG_EOR);
	if (bytes == strlen(reply.c_str()))
		log(INFO, "Sent: \t", reply);
}
