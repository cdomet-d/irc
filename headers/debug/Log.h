/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Log.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:36:08 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/19 14:11:09 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedef.hpp"

//TODO : should I remove this file ?
enum logEnum { INFO, ERROR, DEBUG };
void reply::log(logEnum level, std::string message);
void reply::log(logEnum level, std::string message, std::string additionalInfo);
