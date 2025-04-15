#include <string>

namespace RPL {
	enum e_level { INFO, ERROR, DEBUG, REPLY, GOT };
	void log(e_level level, std::string message, std::string verbose);
	void log(e_level level, std::string message);
	void send_(int fd, std::string reply);

} // namespace RPL