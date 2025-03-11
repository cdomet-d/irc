/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InputTokenizer.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:14:51 by csweetin          #+#    #+#             */
/*   Updated: 2025/03/03 17:12:20 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdParam.hpp"

void	splitOnComa(std::string& buffer, CmdParam& param)
{
	size_t i = 0;
	size_t	index = 0;

	while (i < buffer.size() && buffer[i] != ' ')
	{
		index = buffer.find_first_of(", ", 0);
		if (index == std::string::npos)
			index = buffer.size();
		param.getParam().push_back(buffer.substr(0, index));
		if (buffer[index] != ' ')
			index++;
		buffer.erase(0, index);
	}
	if (buffer[i] == ' ')
		while (i < buffer.size() && buffer[i] == ' ')
			buffer.erase(0, 1);
}

