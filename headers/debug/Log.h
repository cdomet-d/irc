/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Log.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:36:08 by aljulien          #+#    #+#             */
/*   Updated: 2025/02/25 16:54:19 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Colors.hpp"
#include <ctime>
#include <iostream>
#include <string>

//TODO : should I remove this file ?
enum logLevel { INFO, ERROR, DEBUG };
void log(logLevel level, std::string message);
