#include <string>

namespace cmd {
	void join(const int fd, const std::string &target);
	void answer(const int fd, const std::string &target);

	//TODO: figure out why the bot can't reconnect afterward
	//TODO: kick all clients in bot channel so it can be closed when ft-friend quits
	void disconnect(const int fd);

	bool parseLogin(std::string &login);
} // namespace cmd