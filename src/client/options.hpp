#ifndef CLIENT_OPTIONS_HPP
#define CLIENT_OPTIONS_HPP

#include <iostream>

namespace client {

	struct options {
		bool show_usage;
		bool show_help;
		bool show_version;

		options()
			: show_usage(false)
			, show_help(false)
			, show_version(false)
		{}
	};

}

client::options process_command_line(int argc, char const* argv[]);
std::ostream& show_usage(std::ostream& stream);
std::ostream& show_help(std::ostream& stream);

#endif // CLIENT_OPTIONS_HPP
