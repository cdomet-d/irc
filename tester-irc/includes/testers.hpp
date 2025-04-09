/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:42:36 by csweetin          #+#    #+#             */
/*   Updated: 2025/04/03 15:59:22 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTERS_HPP
#define TESTERS_HPP
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

int test(const char *script, const char *expectedOutputFile,
         const char *testName);

#endif