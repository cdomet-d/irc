/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:59:33 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/10 10:12:37 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_HPP
#define TYPEDEF_HPP

// -------------------------------- DATA TYPES ------------------------------ //

#define clientMap std::map< int, Client * >
#define clientPair std::pair< int, Client * >
#define clientMapIt std::map< int, Client * >::iterator
#define channelMap std::map< std::string, Channel * >
#define channelMapIt std::map< std::string, Channel * >::iterator
#define stringVec std::vector< std::string >

// -------------------------------- IRC UTILS ------------------------------- //

#define MAX_EVENTS 100
#define MESSAGE_TERMINATION "\r\n"

// -------------------------------- DEBUG ----------------------------------- //

#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define BG_BLACK "\033[40m"
#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN "\033[46m"
#define BG_WHITE "\033[47m"
#define RESET "\033[0m"

#endif