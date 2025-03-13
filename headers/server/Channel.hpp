/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:38 by aljulien          #+#    #+#             */
/*   Updated: 2025/03/13 15:41:07 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "typedef.hpp"

class Client;

class Channel {
  public:
	/*                               ORTHODOX CLASS                           */
	Channel(std::string name);
	~Channel(void);

	/*                               METHODS                                  */
	bool addClientToChan(Channel *curChan, Client *curCli);

	/*                               GETTERS                                  */
	bool getInviteOnly() const;
	bool getIsPassMatch() const;
	bool getTopicRestrict() const;
	clientMap &getCliInChan();
	clientMap &getOpCli();
	int getMaxCli() const;
	std::string getName() const;
	std::string getTopic() const;
	std::string getModes() const;
	std::string getPassword() const;

	/*                               SETTERS                                  */
	void setInviteOnly(bool inviteOnly);
	void setIsPassMatch(bool password);
	void setMaxCli(int maxCli);
	void setModes();
	void setName(std::string name);
	void setPassword(std::string password);
	void setTopic(std::string topic);
	void setTopicRestrict(bool topicRestrict);

  private:
	bool inviteOnly_;
	bool isPassMatch_;
	bool topicRestrict_;
	clientMap cliInChan_;
	clientMap cliIsOperator_;
	int maxCli_;
	std::string modes_;
	std::string name_;
	std::string pass_;
	std::string topic_;
};

#endif
