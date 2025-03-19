/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Log.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:36:08 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/18 09:09:22 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedef.hpp"

//TODO : should I remove this file ?
enum logEnum { INFO, ERROR, DEBUG };
void logLevel(logEnum level, std::string message);
void logLevel(logEnum level, std::string message, std::string additionalInfo);
