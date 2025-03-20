/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/03/20 12:38:10 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Client.hpp"
#include "Reply.hpp"
#include "typedef.hpp"

enum mapChan { ALLCLI, OPCLI, INVITECLI };

class Client;

class Channel {
  public:
	/*                               ORTHODOX CLASS                           */
	Channel(std::string name);
	~Channel(void);

	/*                               METHODS                                  */
	bool addClientToChan(Channel *curChan, Client *curCli);
	void printMapValues();
	void addCli(mapChan curMap, Client *curCli);
	void removeCli(mapChan curMap, int fdCli);

	/*                               GETTERS                                  */
	bool getInviteOnly() const;
	bool getIsPassMatch() const;
	bool getTopicRestrict() const;
	const clientMap &getCliInChan() const;
	const clientMap &getOpCli() const;
	const clientMap &getInvitCli() const;
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
	clientMap cliInvited_;
	size_t maxCli_;
	std::string modes_;
	std::string name_;
	std::string pass_;
	std::string topic_;
};

void sendMessageChannel(clientMap allCliChannel, std::string message);

#endif
