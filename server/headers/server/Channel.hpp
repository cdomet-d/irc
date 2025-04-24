/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:38 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/24 09:45:36 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Client.hpp"
#include "Reply.hpp"
#include "typedef.hpp"
#include "CmdSpec.hpp"

enum mapChan { ALLCLI, OPCLI, INVITECLI };

class Client;
class CmdSpec;

class Channel {
  public:
	/*                               ORTHODOX CLASS                           */
	Channel(std::string name);
	~Channel();

	/*                               METHODS                                  */
	bool addClientToChan(Channel *curChan, Client *curCli);
	void addCli(mapChan curMap, Client *curCli);
	void removeCli(mapChan curMap, int fdCli);
	void checkOnlyOperator(Client &oldOp);
	void partOneChan(Client *sender, Channel &curChan);
	static void partAllChans(CmdSpec &cmd, const std::string &message);
	void partMess(Client *sender, Channel &curChan, const std::string &message);

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
	int maxCli_;
	std::string modes_;
	std::string name_;
	std::string pass_;
	std::string topic_;
};

#endif
