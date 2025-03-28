/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:59:33 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/03/28 11:33:25 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_HPP
#define TYPEDEF_HPP

#include <map>
#include <string>
#include <vector>

class Client;
class Channel;

// -------------------------------- DATA TYPES ------------------------------ //

typedef std::map< int, Client * > clientMap;
typedef std::map< int, Client * >::const_iterator clientMapIt;
typedef std::map< std::string, int > nickMap;
typedef std::map< std::string, Channel * > channelMap;
typedef std::map< std::string, Channel * >::const_iterator channelMapIt;
typedef std::pair< int, Client * > clientPair;
typedef std::pair< std::string, int > nickPair;
typedef std::vector< std::string > stringVec;

/* assess the type of the mode flag */
typedef enum {
	/* TYPE_ERR: is unknown flag */
	TYPE_ERR,
	/* TYPE B: always MUST have a param */
	B,
	/* TYPE C: MUST have a param when set, MUST NOT have a param when unset	*/
	C,
	/* TYPE D: MUST NOT have a param */
	D
} e_mdetype;

/* assess whether the mode is being set '+' or unset '-' */
typedef enum {
	SET_ERR,
	SET,
	UNSET,
} e_mdeset;

// -------------------------------- IRC UTILS ------------------------------- //

#define MAX_EVENTS 100
#define MAX_CHAN_PER_CLI 50

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