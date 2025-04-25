/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Api.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:51:31 by csweetin          #+#    #+#             */
/*   Updated: 2025/04/25 10:24:28 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef API_HPP
#define API_HPP

#include "Reply.hpp"
#include "Utils.hpp"
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fcntl.h>
#include <fstream>
#include <sys/wait.h>

class Api {
  public:
	/*                               ORTHODOX CLASS                           */
	Api(void);
	Api(char **envp);
	Api(const Api &rhs);
	Api &operator=(const Api &rhs);
	~Api(void);

	/*                               METHODS                                  */
	bool curlStatus(int status);
	bool executeCmd(void);
	bool fillCmd(void);
	bool findCurlPath();
	bool findSecret();
	bool openFile();
	bool requestLocation(const int fd, const std::string &target,
						 const std::string &login);
	bool requestToken();
	std::string findStr(const std::string &strToFind);
	void cleanChild(int exitCode);

	/*                               GETTERS                                  */
	std::string getEnvVar(const std::string &varName);
	const std::string &getPos(void) const;

	/*                               SETTERS                                  */

  private:
	/*                               MEMBERS                                  */
	char **cmd_;
	char **envp_;
	int resFd_;
	std::string clientIUD_;
	std::string curlPath_;
	std::string pos_;
	std::string secret_;
	std::string token_;
	std::string URL_;
	std::time_t time_;
	std::vector< std::string > curlCmd_;
};

#endif
