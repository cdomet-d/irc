/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserInfo.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:04:32 by cdomet-d          #+#    #+#             */
/*   Updated: 2025/04/23 16:23:01 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERINFO_HPP
#define USERINFO_HPP

#include <string>

class UserInfo {
  public:
	/*                               ORTHODOX CLASS                           */
	UserInfo();
	~UserInfo();

	/*                               METHODS                                  */

	/*                               GETTERS                                  */
	int getRegistration() const;
	const std::string &getHostname() const;
	const std::string &getIP() const;
	const std::string &getName() const;
	const std::string &getNick() const;
	const std::string &getPrefix() const;
	const std::string &getRealName() const;
	const std::string &getUsername() const;

	/*                               SETTERS                                  */
	void setHostname(std::string hostname);
	void setIP(std::string ip);
	void setNick(const std::string &newNick);
	void setPrefix();
	void setRealname(const std::string &realname);
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
