/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Log.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:36:08 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/11 14:11:56 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedef.hpp"
#include <ctime>
#include <iostream>
#include <string>

//TODO : should I remove this file ?
enum logLevel { INFO, ERROR, DEBUG };
void log(logLevel level, std::string message);
void log(logLevel level, std::string message, std::string additionalInfo);
