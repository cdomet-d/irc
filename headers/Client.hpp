/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:28:43 by aljulien          #+#    #+#             */
/*   Updated: 2025/02/19 17:17:45 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <vector>

class Client {
  public:
	/*                               ORTHODOX CLASS                           */
	Client(void);
	Client(const Client &rhs);
	~Client(void);
	Client &operator=(const Client &rhs);

	/*                               METHODS                                  */

	/*                               GETTERS                                  */
	std::string getName() const;
	std::string getNick() const;
	std::string getRealName() const;
	std::string getOpStatus() const;
	/*                               SETTERS                                  */
	void setOpStatus(bool isOp);

  private:
	// TODO: do we need a password ?

	// user info
	std::string _name;
	std::string _realName;
	std::string _nick;
	bool isOp;

	// channels
	std::vector< int > joinedChans;
	
	/*                               METHODS                                  */
	// parsing
	bool isValidNick(g)
};

#endif
