/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:38 by aljulien          #+#    #+#             */
/*   Updated: 2025/04/24 16:15:47 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Client.hpp"
#include "CmdSpec.hpp"
#include "Reply.hpp"
#include "typedef.hpp"

enum mapChan { ALLCLI, OPCLI, INVITECLI };

class Client;
class CmdSpec;

class Channel {
  public:
	/*                               ORTHODOX CLASS                           */
	Channel(std::string name);
	~Channel();

	/*                               METHODS                                  */
	bool addClientToChan(Channel &curChan, Client &curCli);
	Client &getCliFromNick(const std::string &targetNick) const;
	static Channel &createChan(const std::string &chanName);
	static void partAllChans(CmdSpec &cmd, const std::string &message);
	void addCli(const mapChan &curMap, Client &curCli);
	void checkOnlyOperator(Client &oldOp);
	void partMess(const Client &sender, const Channel &curChan,
				  const std::string &message);
	void partOneChan(Client &sender, Channel &curChan);
	void removeCli(const mapChan &curMap, int fdCli);

	/*                               GETTERS                                  */
	bool getInviteOnly() const;
	bool getIsPassMatch() const;
	bool getTopicRestrict() const;
	const clientMap &getCliInChan() const;
	const clientMap &getInvitCli() const;
	const clientMap &getOpCli() const;
	const std::string &getModes() const;
	const std::string &getName() const;
	const std::string &getPassword() const;
	const std::string &getTopic() const;
	int getMaxCli() const;

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

	Channel();
	Channel(const Channel &rhs);
	Channel operator=(const Channel &rhs);
};

#endif
