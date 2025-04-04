/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserInfo.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:04:32 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/04 13:39:45 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERINFO_HPP
#define USERINFO_HPP

#include <string>
class UserInfo {
  public:
	/*                               ORTHODOX CLASS                           */
	UserInfo(void);
	~UserInfo(void);

	/*                               METHODS                                  */

	/*                               GETTERS                                  */
	int getRegistration() const;
	std::string getHostname() const;
	std::string getIP() const;
	std::string getName() const;
	std::string getNick() const;
	std::string getPrefix() const;
	std::string getRealName() const;
	std::string getUsername() const;

	/*                               SETTERS                                  */
	void setHostname(std::string hostname);
	void setIP(std::string ip);
	void setNick(const std::string &newNick);
	void setPrefix();
	void setRegistration(int stage);
	void setUsername(const std::string &username);

  private:
	int registration_;
	std::string hostname_;
	std::string ip_;
	std::string name_;
	std::string nick_;
	std::string pass_;
	std::string prefix_;
	std::string realName_;
	std::string username_;

	UserInfo(const UserInfo &rhs);
	UserInfo &operator=(const UserInfo &rhs);
};

#endif
