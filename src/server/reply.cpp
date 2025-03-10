/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:37:38 by aljulien          #+#    #+#             */
/*   Updated: 2025/02/28 13:40:32 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Log.h"
#include "reply.h"
#include <sys/socket.h>

void sendReply(int fd, std::string reply) {
	size_t bytes = send(fd, reply.c_str(), strlen(reply.c_str()), MSG_EOR);
	if (bytes == strlen(reply.c_str()))
		log(INFO, "Message send in full");
}
